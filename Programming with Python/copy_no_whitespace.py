def remove_whitespace_and_copy(source_file, destination_file):
    try:
        with open(source_file, 'r') as f_src:
            content = f_src.read()
        
        # Remove all whitespace characters (spaces, tabs, newlines, etc.)
        cleaned_content = ''.join(content.split())

        with open(destination_file, 'w') as f_dest:
            f_dest.write(cleaned_content)

        print(f"Contents copied from '{source_file}' to '{destination_file}' after removing whitespaces.")
    
    except FileNotFoundError:
        print(f"Source file '{source_file}' not found.")
    except Exception as e:
        print("An error occurred:", e)

# Example usage
if __name__ == "__main__":
    source = input("Enter source filename (e.g. source.txt): ")
    destination = input("Enter destination filename (e.g. dest.txt): ")
    remove_whitespace_and_copy(source, destination)
