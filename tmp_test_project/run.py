import platform
import subprocess

app_name: str = "tmp_test_project"

if platform.system() == "Windows":
	subprocess.run("rmdir /S /Q build", shell = True)
else:
	subprocess.run("rm -rf build", shell = True)

subprocess.run("mkdir build", shell=True)

result = subprocess.run(f"conan install . --build=missing -of build && cmake . -B build && make -C build", check=True, shell=True)

if result.stdout:
	print(result.stdout.decode())
else:
	print("No output from the command.")

if platform.system() == "Windows":
	subprocess.run([f".\\build\\{app_name}.exe"], check = True)
else:
	subprocess.run([f"./build/{app_name}"], check = True)
