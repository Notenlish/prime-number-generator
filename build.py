import os

platforms = {
    "main-windows-arm.exe":"aarch64-windows-gnu",
    "main-windows-x86.exe":"x86_64-windows-gnu",
    "main-linux-x86":"x86_64-linux-gnu",
    "main-linux-arm":"aarch64-linux-gnu",
    "main-macos-x86":"x86_64-macos",
    "main-macos-arm":"aarch64-macos",
}

for name,platform in platforms.items():
    os.system(f"zig cc src/main.c -o dist/{name} -target {platform}")

print("Done!")