import click
import os
import zipfile

include = ['.cpp', '.fs', '.vs']


@click.command()
@click.argument('assignment_number', type=int)
def collect_submittables(assignment_number):
    zip_filename = f'CSCD377KorchemniyA{assignment_number}.zip'
    source_dir = f'.\\Assignment{assignment_number}\\Assignment{assignment_number}\\'

    with zipfile.ZipFile(zip_filename, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, _, files in os.walk(source_dir):
            for file in files:
                _, ext = os.path.splitext(file)
                if ext in include:
                    file_path = os.path.join(root, file)
                    zipf.write(file_path, os.path.relpath(file_path, source_dir))


if __name__ == "__main__":
    collect_submittables()
