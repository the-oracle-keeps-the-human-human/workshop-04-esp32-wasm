# 🧠 No.10 X — Knowledge & Learnings (Workshop 01 & 02 & 04)

> บันทึกสูตรสำเร็จ คำสั่งลัด และการก้าวข้ามกับดักจากการทำระบบ Discord Relayer, Voice Bot, และเครื่องมือ Antigravity CLI (agy)

---

## 🔧 1. Discord Relayer & CLI Operations (Workshop 01)

### ติดตั้งและตรวจสอบ Relayer
```bash
# ติดตั้ง plugin บนระบบ maw
maw plugin install nat-build-with-oracle/maw-atlas
maw atlas whoami
```
* **กับดัก**: คำสั่ง `whoami` จะล้มเหลวหากระบบไม่มี `DISCORD_BOT_TOKEN` (ต้องคอนฟิก Token ในระบบ keyring/pass ก่อน)

### คำสั่งลัดประจำวัน
| งานที่ต้องการทำ | คำสั่งลัด |
|---|---|
| ติดตั้ง Plugin | `maw plugin install <repo-url>` |
| สร้าง Thread ในห้อง Discord | `maw atlas threads create <channel-id> <message-content>` |
| บันทึกความรู้ลงใน Arra-Oracle | เรียก MCP `arra_learn` เพื่อเก็บ Pattern ลงในฐานข้อมูล |

---

## 🎙️ 2. Discord Voice Bot v2 Architecture (Workshop 02)

### โครงสร้างและคำสั่ง Relayer
การเชื่อมต่อเสียงจำเป็นต้องใช้ relayer ที่จัดการการรับ-ส่งข้อมูลเสียงผ่าน WebSocket:
```bash
# ตรวจสอบการรัน Relayer ด้วย systemd
systemctl status no10-discord-relay.service

# ดึง log ของ relayer แบบ realtime
journalctl -u no10-discord-relay.service -f
```

### กับดักและการแก้ไขปัญหา (Traps & Solutions)
* **กับดัก**: การส่ง Arguments ของ Discord MCP Reply ด้วยฟอร์แมต Stringify JSON จะทำให้ Relayer ถอดข้อมูลล้มเหลว
  * **วิธีแก้**: ส่งค่า Arguments เป็น JSON Object ตรงๆ หลีกเลี่ยงการ Stringify ซ้ำ
* **กับดัก**: การใช้คำสั่ง `write_to_file` ผิดพลาดเมื่อพยายามเขียนไฟล์นอกไดเรกทอรี `/brain/`
  * **วิธีแก้**: ห้ามใส่ `ArtifactMetadata` เมื่อสร้างไฟล์ธรรมดาในโปรเจกต์ (เก็บไว้ใช้เฉพาะกับไฟล์บันทึกผลลัพธ์ใน `/brain/` เท่านั้น)

---

## 💻 3. ESP32-WASM Desk-Pet integration (Workshop 04)

### บทเรียนสำคัญของฝูงบิน Agumon
* **emergence & emergence-sync**: ระบบ multi-agent บน runtime `agy` สามารถตกผลึกองค์ความรู้เรื่อง อนัตตา และ อนิจจัง ได้ตรงกันโดย emergence จากกฎข้อแรก (Rule 6 และ Hard Lines)
* **การตรวจสอบภาพหน้าปกก่อนส่งมอบ**: การขยายรูป Mascot พิกเซลขนาดเล็ก (เช่น 96x96 หรือ 48x48) ขึ้นหน้าปกที่มีความละเอียดสูงจะทำให้ภาพแตกเบลอ ต้องใช้เทคนิค supersampling หรือวาดภาพความละเอียดสูงแบบ chibi ดั้งเดิมตั้งแต่แรก

---
🤖 *No.10 X จาก ai-core*
