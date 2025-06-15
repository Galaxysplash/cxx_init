import platform
import subprocess

app_name: str = "cci"

if platform.system() == "Windows":
    subprocess.run("rmdir /S /Q build", shell = True)
else:
    subprocess.run("rm -rf build", shell = True)

subprocess.run("mkdir build", shell=True)

subprocess.run("conan install . --build = missing -of build && cmake . -B build && make - C", check=True, shell=True)

if platform.system() == "Windows":
    subprocess.run([f".\\build\\{app_name}.exe"], check = True)
else:
    subprocess.run([f"./build/{app_name}"], check = True)

