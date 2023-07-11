import os
import platform
import subprocess

def run_command(command):
    subprocess.run(command, shell=True)

current_platform = platform.system()

if current_platform == "Windows":
    build_command = 'cmake -G "MinGW Makefiles" -S . -B build && cmake --build build --config release'
else:
    build_command = 'cmake -S . -B build && cmake --build build --config release'

run_command(build_command)