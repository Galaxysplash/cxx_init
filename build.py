import platform
import subprocess

app_name: str = "cxx_init"

subprocess.run("rm -r build &&cmake . -B build && make -C build", shell=True)

if platform.system() == "Windows":
	subprocess.run([f"./build/{app_name}.exe"], check = True)
else:
	subprocess.run([f"./build/{app_name}"], check = True)
