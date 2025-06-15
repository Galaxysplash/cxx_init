import os
import platform
import subprocess

project_name: str = "tmp_test_project"

if platform.system() == "Windows":
	subprocess.run("rmdir /S /Q build", shell = True)
else:
	subprocess.run("rm -rf build", shell = True)

if not os.path.exists("build"):	subprocess.run("mkdir build", shell=True)

result = subprocess.run(f"conan install . --build=missing -of build && cmake . -B build && make -C build", check=True, shell=True)

if result.stdout:
	print(result.stdout.decode())
if platform.system() == "Windows":
	if os.path.exists(f".\\build\\{project_name}"):		subprocess.run([f".\\build\\{project_name}.exe"], check = True)
else:
	if os.path.exists(f"./build/{project_name}"):		subprocess.run([f"./build/{project_name}"], check = True)
