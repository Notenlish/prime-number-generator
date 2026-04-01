import os
import zipfile
import pathlib
import shutil

platforms = {
    "main-windows-arm.exe":"aarch64-windows-gnu",
    "main-windows-x86.exe":"x86_64-windows-gnu",
    "main-linux-x86":"x86_64-linux-gnu",
    "main-linux-arm":"aarch64-linux-gnu",
    "main-macos-x86":"x86_64-macos",
    "main-macos-arm":"aarch64-macos",
}

if not pathlib.Path("build").exists():
    pathlib.Path.mkdir("build")
if not pathlib.Path("dist").exists():
    pathlib.Path.mkdir("dist")

for name,platform in platforms.items():
    graph_name = name.replace("main-", "graph-")

    print(f"Building for {name}.")
    os.system(f"zig cc src/main.c -o build/{name} -target {platform}")
    os.system(f"zig cc src/graph.c src/pbPlots.c src/supportLib.c -o build/{graph_name} -target {platform}")

    print(f"Zipping release for {name}.")

    zip = zipfile.ZipFile(f"dist/{name}.zip", "w", zipfile.ZIP_DEFLATED)
    zip.write(f"build/{name}", name)
    zip.write(f"build/{graph_name}", graph_name)
    zip.close

print("Done!")