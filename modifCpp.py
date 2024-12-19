import os
import re

def list_files_with_tu(base_dir, exts):
    matching_files = []
    for root, dirs, files in os.walk(base_dir):
        for file in files:
            if file.endswith(exts):
                full_path = os.path.join(root, file)
                if os.path.normpath('/TU/') in os.path.normpath(full_path):
                    matching_files.append(full_path)
    return matching_files

def extract_class_name_and_test_name(file_path):
    class_pattern = r'class\s+(\w+)\s*:'  # Pattern pour capturer le nom de la classe
    test_pattern = r'CPPUNIT_TEST\((\w+)\)'  # Pattern pour capturer les mots dans CPPUNIT_TEST
    class_name = None
    test_cases = []
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            for line in file:
                if class_name is None:
                    match = re.search(class_pattern, line)
                    if match:
                        class_name = match.group(1)
                test_cases.extend(re.findall(test_pattern, line))
    except FileNotFoundError:
        print(f"Fichier non trouvé : {file_path}")
    except Exception as e:
        print(f"Erreur lors de la lecture du fichier : {e}")
    return class_name, test_cases

def extract_class_test_methods(files):
    results = []
    for file in files:
        if file.endswith('.h'):
            class_name, test_cases = extract_class_name_and_test_name(file)
            if class_name:
                results.extend([f"{class_name}:{test_case}" for test_case in test_cases])
    return results

def process_cpp_files(files, methods):
    """
    Modifie les fichiers .cpp pour insérer `setTestSummary` juste après `setTestCase`.
    Gère les méthodes de classe sous la forme `ClassName::methodName`.
    """
    method_names = {method.split(":")[1]: method.split(":")[0] for method in methods}
    hook_line_pattern = r'CustomHook::instance\(\)->setTestCase\('
    summary_pattern = r'CustomHook::instance\(\)->setTestSummary\('
    comment_pattern = r'^\s*//.*'  # Match les lignes de commentaires
    method_pattern = r'^\s*\w+\s+(\w+\s*::\s*\w+)\s*\(.*\)\s*{'  # Gère les types de retour

    for file_path in files:
        if not file_path.endswith('.cpp'):
            continue
        try:
            with open(file_path, 'r', encoding='utf-8') as file:
                lines = file.readlines()
            modified_lines = []
            comment_block = []
            current_method = None
            has_summary = False

            for i, line in enumerate(lines):
                line = "void Test1::test1Case1() {"
                # Vérifie si la ligne correspond à une méthode de classe
                match = re.match(method_pattern, line)
                if match:
                    current_method = match.group(1)  # Par exemple, `Test1::test1Case1`
                    class_name, method_name = current_method.split("::")
                    has_summary = False

                    # Ajouter le bloc de commentaire comme `setTestSummary` si nécessaire
                    if comment_block and method_name in method_names:
                        summary_code = (
                            f'CustomHook::instance()->setTestSummary("{" ".join(comment_block)}");\n'
                        )
                        modified_lines.append(summary_code)
                        comment_block = []

                # Identifier un appel existant à `setTestSummary`
                if current_method and re.search(summary_pattern, line):
                    has_summary = True

                # Identifier `setTestCase` et insérer `setTestSummary` juste après si nécessaire
                if current_method and re.search(hook_line_pattern, line):
                    modified_lines.append(line)
                    if not has_summary and method_name in method_names:
                        summary_code = (
                            f'CustomHook::instance()->setTestSummary("{" ".join(comment_block)}");\n'
                        )
                        modified_lines.append(summary_code)
                        has_summary = True

                # Accumuler les commentaires avant une méthode
                elif re.match(comment_pattern, line):
                    comment_block.append(line.strip().lstrip("//").strip())

                else:
                    modified_lines.append(line)

            # Écrire les modifications dans le fichier
            with open(file_path, 'w', encoding='utf-8') as file:
                file.writelines(modified_lines)

        except Exception as e:
            print(f"Erreur lors du traitement du fichier {file_path} : {e}")

# Exemple d'utilisation
base_directory = "src"  # Remplace par le chemin de ton dossier de base
files = list_files_with_tu(base_directory, ('.cpp', '.h'))
test_methods = extract_class_test_methods(files)
process_cpp_files(files, test_methods)
