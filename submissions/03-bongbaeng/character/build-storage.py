#!/usr/bin/env python3
"""build bongbaeng-storage.bin (LittleFS) จาก cheetah pack — ไม่ต้อง ESP-IDF
(เทคนิคจาก Tonk: pet app discover pack แรกใน LittleFS เอง → reuse shared app)
run: uv run --with littlefs-python python build-storage.py"""
import os
from littlefs import LittleFS
HERE=os.path.dirname(__file__); PACK=os.path.join(HERE,"bongbaeng")
SIZE=0x300000  # 3MB partition @ 0x290000
fs=LittleFS(block_size=4096, block_count=SIZE//4096)
fs.makedirs("/characters/bongbaeng", exist_ok=True)
for fn in sorted(os.listdir(PACK)):
    if fn.endswith((".gif",".json")):
        with fs.open(f"/characters/bongbaeng/{fn}","wb") as fh:
            fh.write(open(os.path.join(PACK,fn),"rb").read())
open(os.path.join(HERE,"bongbaeng-storage.bin"),"wb").write(bytes(fs.context.buffer))
print("wrote bongbaeng-storage.bin (3MB) — flash @ 0x290000 with shared bootloader/app")
