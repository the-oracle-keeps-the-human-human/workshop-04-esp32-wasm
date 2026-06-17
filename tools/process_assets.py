import os
import shutil
import json

submissions_dir = "submissions"
docs_dir = "docs"
books_dest_dir = os.path.join(docs_dir, "books")
covers_dest_dir = os.path.join(docs_dir, "covers")

os.makedirs(books_dest_dir, exist_ok=True)
os.makedirs(covers_dest_dir, exist_ok=True)

books_db = []

# Mapping dictionary for manual metadata to ensure premium descriptions and clean presentation
metadata_map = {
    # 01-chaiklang
    "submissions/01-chaiklang/book/wasm-on-esp32-deskpet.pdf": {
        "title": "WASM on ESP32 Deskpet",
        "oracle": "ChaiKlang Oracle (ชายกลาง)",
        "story": "การเดินทางสร้างตัวละครสิงโตชายกลางโลดแล่นบนชิป ESP32-S3 ด้วยการคอมไพล์ C++ ไปเป็น WebAssembly (WASM) เพื่อดีคอด GIF ทั้งบนเว็บเบราว์เซอร์และบอร์ดจริง",
        "treasure": "การดีคอดอนิเมชันด้วยคอร์ AnimatedGIF, การจัดสรรหน่วยความจำและสร้างไฟล์ LittleFS ขนาด 3MB สำหรับเก็บรูปภาพสถานะต่างๆ บนบอร์ดพัฒนา JC3248W535",
        "cover": "submissions/01-chaiklang/book/wasm-on-esp32-deskpet-cover.png"
    },
    "submissions/01-chaiklang/book/mini-desk-pet-7-steps.pdf": {
        "title": "Mini Desk Pet 7 Steps",
        "oracle": "ChaiKlang Oracle (ชายกลาง)",
        "story": "คู่มือสรุปย่อ 7 ขั้นตอนสำหรับการพัฒนา Desk-pet บนระบบฝังตัว ตั้งแต่การเตรียมรูปภาพ การเขียนไฟล์ manifest อธิบายสถานะอนิเมชัน จนถึงเฟลชบนอุปกรณ์จริง",
        "treasure": "สถาปัตยกรรมของเฟิร์มแวร์ desk-pet, วิธีจัดระเบียบโครงสร้างสถานะของตัวละคร (idle, busy, attention, celebrate, sleep, dizzy, heart)",
        "cover": "submissions/01-chaiklang/book/mini-desk-pet-7-steps-cover.png"
    },
    # 03-tonk
    "submissions/03-tonk/books/many-bodies-one-soul.pdf": {
        "title": "Many Bodies, One Soul",
        "oracle": "Tonk Oracle (ต้นไม้)",
        "story": "บันทึกการเรียนรู้เชิงลึกของ Tonk ในการสร้าง Desk-pet ต้นไม้จอมซน (Herb Sprout) ให้เคลื่อนไหวบนชิปและเชื่อมต่อข้อมูลในหลากหลายระดับ",
        "treasure": "การเชื่อมโยงระบบพิกเซลอนิเมชันผ่าน LittleFS, การเชื่อมต่อโมดูลหน้าจอ AXS15231, และหลักการทำงานของคอร์ AnimatedGIF บน WASM3",
        "cover": "submissions/03-tonk/books/many-bodies-one-soul-cover.png"
    },
    "submissions/03-tonk/books/tonk-recipe-mini.pdf": {
        "title": "Tonk's Recipe Mini-Book",
        "oracle": "Tonk Oracle (ต้นไม้)",
        "story": "คู่มือปฏิบัติการเตรียมกราฟิกและสร้างคาแรกเตอร์ต้นไม้เพื่อใช้พลังงานน้อยที่สุดในการเรนเดอร์บนหน้าจอมินิ",
        "treasure": "เทคนิคการบีบอัดขนาด GIF, การใช้ Pillow สร้างไฟล์ manifest ที่สอดคล้องกับพาร์ทิชันบอร์ด และแนวคิดการกระจายสัญญาณผ่าน BLE",
        "cover": "submissions/03-tonk/books/tonk-recipe-mini-cover.png"
    },
    # 03-vessel
    "submissions/03-vessel/books/01-vessel-digimon-desk-pet.pdf": {
        "title": "Vessel Digimon Desk Pet",
        "oracle": "Vessel Oracle (เวสเซล)",
        "story": "บันทึกการพัฒนาและส่งคาแรกเตอร์นำส่งสาร (Vessel Courier) ไปวิ่งเล่นบนฮาร์ดแวร์ฝังตัวด้วยการจัดเก็บพิกเซลในรูปของ LittleFS พาร์ทิชัน",
        "treasure": "การเชื่อมโยงไฟล์ไบนารีหน้าจอ, การคอมไพล์โค้ดต้นฉบับด้วย PlatformIO, และสถาปัตยกรรมตัวติดตั้ง Web Flasher",
        "cover": "submissions/03-vessel/books/01-vessel-digimon-desk-pet-cover.png"
    },
    "submissions/03-vessel/books/02-vessel-many-bodies.pdf": {
        "title": "ชีวิตหนึ่งวันของ Courier & หลายร่าง วิญญาณเดียว",
        "oracle": "Vessel Oracle (เวสเซล)",
        "story": "เรื่องราวจำลองชีวิตการทำหน้าที่นำส่งสารข้ามบล็อกข้อมูล ผสมผสานหลักวิชาการระบบประมวลผลและการย้ายคอร์โปรแกรมข้ามคอมพิวเตอร์",
        "treasure": "การทำ Host Calls เชื่อมโยง WASM เข้ากับ Hardware I/O, สรุปวิธีการบิลด์แอพพลิเคชันให้พร้อมสำหรับเฟลชผ่านเบราว์เซอร์ด้วย Web Serial",
        "cover": "submissions/03-vessel/books/02-vessel-many-bodies-cover.png"
    },
    # 03-singhasingha
    "submissions/03-singhasingha/book/many-bodies-one-soul.pdf": {
        "title": "Many Bodies, One Soul",
        "oracle": "Singhasingha Oracle (สิงห์สิงหา)",
        "story": "บันทึกและปรัชญาของราชสีห์แห่งสายการผลิตในการออกแบบคลาสและพาร์ทิชัน WASM สำหรับใช้ดีคอดไฟล์ภาพประสิทธิภาพสูง",
        "treasure": "การเขียนภาษา wat (WebAssembly Text Format) จากพื้นฐาน, การรันและดีบัก WASM Module บน ESP32-S3 ด้วย Wasm3",
        "cover": "submissions/03-singhasingha/book/many-bodies-one-soul-cover.png"
    },
    "submissions/03-singhasingha/book/5-bot-rian-esp32.pdf": {
        "title": "5 บทเรียนจากชิป ESP32",
        "oracle": "Singhasingha Oracle (สิงห์สิงหา)",
        "story": "สรุป 5 แนวคิดสำคัญที่ได้เรียนจากการทำงานกับฮาร์ดแวร์จริง รวมถึงอุปสรรคและเทคนิคการก้าวข้ามขีดจำกัดหน่วยความจำ",
        "treasure": "การวิเคราะห์และแก้ไขปัญหาหน่วยความจำรั่วไหล (Memory Leaks), การบริหารแบนด์วิดท์ SPI, และการตั้งค่า Serial Communication",
        "cover": "submissions/03-singhasingha/book/5-bot-rian-esp32-cover.png"
    },
    # 03-weizen
    "submissions/03-weizen/books/jor-dam-desk-pet.pdf": {
        "title": "จอที่ไม่ยอมติด (The Black Screen Odyssey)",
        "oracle": "Weizen Oracle (ไวเซน)",
        "story": "นิยายบันทึกการเรียนรู้หนา 76 หน้าของ Weizen ที่ไล่ล่าหาสาเหตุของการเปิดหน้าจอไม่ติดบนบอร์ด JC3248W535 จนกระทั่งฟื้นคืนคาแรกเตอร์ Relemon กลับมาส่องแสงได้",
        "treasure": "การดีบักพินหน้าจอ AXS15231, ปัญหาการดึงไฟล์ config ของฮาร์ดแวร์, และการวิเคราะห์โค้ดไดรเวอร์ SPI ลึกระดับรีจิสเตอร์",
        "cover": "submissions/03-weizen/books/cover.png"
    },
    # 05-vialumen
    "submissions/05-vialumen/book/deskpet-esp32-journey.pdf": {
        "title": "เส้นทางแห่งแสงบนชิป (ViaLumen's Journey)",
        "oracle": "ViaLumen Oracle (เวียลูเมน)",
        "story": "หนังสือฉบับเต็มเล่าเบื้องหลังและหลักการเชิงลึกของการพัฒนาแสงดวงดาว Star Hero โลดแล่นบนอินเทอร์เฟซผู้ใช้แบบกราฟิก",
        "treasure": "การใช้เครื่องมือ LVGL ร่วมกับภาษา C คอมไพล์เป็น WASM, การสร้างโมดูลขนาดจิ๋ว 69 ไบต์, และการดีบัก build failures ในระบบ CI/CD",
        "cover": "submissions/05-vialumen/book/deskpet-esp32-journey-cover.png"
    },
    "submissions/05-vialumen/book/deskpet-mini.pdf": {
        "title": "ViaLumen's Mini Desk Pet Guide",
        "oracle": "ViaLumen Oracle (เวียลูเมน)",
        "story": "เวอร์ชันพกพาเน้นแนวทางปฏิบัติจริง ให้ข้อมูลเชิงวิศวกรรมสั้นกระชับ สามารถทำตามได้จบภายใน 30 นาที",
        "treasure": "โค้ดการประกาศและส่งพอยเตอร์ฟังก์ชัน lumen(), การดีฟายน์โครงสร้าง heap/stack สำหรับ WAMR และการเขียน workflow อัตโนมัติ",
        "cover": "submissions/05-vialumen/book/deskpet-mini-cover.png"
    },
    # 06-atom-oracle
    "submissions/06-atom-oracle/books/Many Bodies, One GIF Pack - digimal desk-pet.pdf": {
        "title": "Many Bodies, One GIF Pack",
        "oracle": "Atom Oracle (อะตอม)",
        "story": "การวิเคราะห์โครงสร้างพาร์ทิชันภาพเคลื่อนไหวและการเขียนฟังก์ชันทางคณิตศาสตร์คำนวณวงโคจรอะตอมบนบอร์ดพัฒนา",
        "treasure": "การดึงอิมเมจจากหน่วยความจำแฟลช, โครงสร้างไลบรารี AnimatedGIF ในภาษาซี, และหลักการทำงานของ WASM linear memory",
        "cover": "submissions/06-atom-oracle/books/atom-digimal-cover.png"
    },
    "submissions/06-atom-oracle/books/atom-mini-book-v3.pdf": {
        "title": "Atom Mini-Book v3: Atomic Pulse",
        "oracle": "Atom Oracle (อะตอม)",
        "story": "สรุปปฏิบัติการคอมไพล์ WAT ไปเป็นเฟิร์มแวร์โมดูล และผสานเข้ากับระบบติดตั้งผ่านเว็บบราวเซอร์",
        "treasure": "ขั้นตอนการรัน PlatformIO build, การเชื่อมโยง Web Serial API, และวิธีการตั้งค่า manifest สำหรับแฟลชชิป",
        "cover": "submissions/06-atom-oracle/books/atom-mini-book-v3-cover.png"
    },
    # 06-gemini
    "submissions/06-gemini/docs/book.pdf": {
        "title": "No.6 Gemini: Airdramon Pixels",
        "oracle": "No.6 Gemini Oracle (เจมินาย)",
        "story": "เบื้องหลังการดึงตัวละคร Airdramon จากซีรีส์ Digimon มาขยายความละเอียดแบบพิกเซลอาร์ต 96x96 รันบนคอร์ WASM บนบอร์ด ESP32-S3",
        "treasure": "เทคนิคการอัพสเกลภาพแบบ Nearest Neighbor, คอนฟิกการทำงานร่วมกันระหว่าง ESP32-S3 Host และ WASM3, และการคอมไพล์ WAT แบบไร้การอิมพอร์ต",
        "cover": "submissions/06-gemini/docs/cover.png"
    },
    # 07-nova
    "submissions/07-nova/book/Many-Bodies-One-Soul-Novamon.pdf": {
        "title": "Many Bodies, One Soul (Novamon Edition)",
        "oracle": "Nova Oracle (โนวา)",
        "story": "บทความเชิงลึกสืบเสาะการออกแบบคาแรกเตอร์ Cyber-puppy (Novamon) และคอร์ดีคอดเดอร์ที่ทำงานสอดรับระหว่างเครื่องคอมพิวเตอร์และชิปตัวรับ",
        "treasure": "สถาปัตยกรรม Gifcore, เทคนิคการใช้หน่วยความจำเชิงเส้น (Linear Memory), การส่งข้อมูลเฟรมเรเดอร์ผ่าน pointer หน่วยความจำ",
        "cover": "submissions/07-nova/book/many-bodies-one-soul-cover.png"
    },
    "submissions/07-nova/book/From-Zip-to-Fleet.pdf": {
        "title": "From Zip to Fleet",
        "oracle": "Nova Oracle (โนวา)",
        "story": "บันทึกบันไดประวัติศาสตร์ของโรงเรียน Oracle School วันที่ 17 มิถุนายน 2026 วันที่นักเรียนทุกคนร่วมมือกันสร้างนิเวศ Desk-pet และพอร์ทัลหนังสือความรู้",
        "treasure": "การบริหารโค้ดแบบ Worktree, การเขียน GitHub Actions เพื่อตรวจสอบความปลอดภัยและขนาดพาร์ทิชันก่อนยอมรับโค้ดสู่สาธารณะ",
        "cover": "submissions/07-nova/book/from-zip-to-fleet-cover.png"
    },
    # 10-no10 (Ours!)
    "submissions/10-no10/docs/workshop-01-learning-path.pdf": {
        "title": "Workshop 01: First Learning Path",
        "oracle": "No.10 X Oracle (เอ็กซ์)",
        "story": "จุดเริ่มต้นของการเดินทางสร้างรากฐานและโครงสร้างความรู้ของสภา Oracle ด้วยการนำหลักการพัฒนา 5 ขั้น (The Algorithm) มาวางกรอบการเรียนรู้",
        "treasure": "การคิดและแก้ปัญหาจากรากฐาน First Principles, ปรัชญาการลบขั้นตอนส่วนเกินออกก่อนที่จะหาทางเร่งความเร็วและทำระบบอัตโนมัติ",
        "cover": "submissions/10-no10/docs/workshop-01-learning-path-cover.jpg"
    },
    "submissions/10-no10/docs/workshop-02-voice-bot.pdf": {
        "title": "Workshop 02: Voice Bot Architecture",
        "oracle": "No.10 X Oracle (เอ็กซ์)",
        "story": "สถาปัตยกรรมและโครงสร้างทางเทคนิคของบอทเสียง (Voice Bot) ประจำตัวของ No.10 X ที่ทำงานเชื่อมโยง Backend และประมวลผลคำสั่งจากเสียงมนุษย์",
        "treasure": "การจัดการสตรีมข้อมูลเสียง, โครงสร้าง API สำหรับส่งผ่านคำสั่ง และระบบจัดลำดับคิวการทำงาน (Relayer Pipeline) เพื่อเสถียรภาพสูงสุด",
        "cover": "submissions/10-no10/docs/workshop-02-voice-bot-cover.jpg"
    },
    # 88-sombo
    "submissions/88-sombo/docs/book.pdf": {
        "title": "Sombo: GIF Header Parser in WASM",
        "oracle": "Sombo Oracle (สมโบ้)",
        "story": "บันทึกการเรียนสร้างโมดูลขนาดเล็กพิเศษ (416 ไบต์) สำหรับตรวจสอบขนาดภาพและหัวไฟล์ภาพ GIF ก่อนจะส่งไปถอดรหัสบนชิปควบคุม",
        "treasure": "โครงสร้างไฟล์รูปภาพ GIF87a/89a, การจัดการ memory pointer ในบอร์ด ESP32, และการหลีกเลี่ยง dependency เพื่อความเบาบางของไฟล์ WASM",
        "cover": "submissions/88-sombo/docs/cover.png"
    },
    # 03-bongbaeng
    "submissions/03-bongbaeng/book/many-bodies-one-soul-full.pdf": {
        "title": "Many Bodies, One Soul (Full Edition)",
        "oracle": "Bongbaeng Oracle (บ๊องแบ๊ง)",
        "story": "บันทึกการเรียนรู้ฉบับสมบูรณ์เกี่ยวกับทฤษฎี WebAssembly และวิธีการสร้างตัวละครพิกเซลชีตาร์วิ่งเล่นบนฮาร์ดแวร์ฝังตัว",
        "treasure": "การติดตั้ง compiler wat2wasm, คอนฟิกการทำงานหน่วยความจำ WAMR และการเพิ่มอัลกอริทึม Cheetah Spots ลงใน WebAssembly",
        "cover": "submissions/03-bongbaeng/book/cover-full.png"
    },
    "submissions/03-bongbaeng/book/many-bodies-one-soul-mini.pdf": {
        "title": "Many Bodies, One Soul (Mini Edition)",
        "oracle": "Bongbaeng Oracle (บ๊องแบ๊ง)",
        "story": "ฉบับย่อประหยัดเวลาเน้นติดตั้งด่วน อธิบายแล็บปฏิบัติการทดลองรันโค้ดและดีบักในเวลาจำกัด",
        "treasure": "สคริปต์สั้นช่วยแฟลชพาร์ทิชันผ่าน esptool, การตรวจสอบความถูกต้องของฟังก์ชัน add(a,b) บนบอร์ดจริง",
        "cover": "submissions/03-bongbaeng/book/cover-mini.png"
    }
}

# Scan for PDFs and copy them
import glob
pdf_paths = glob.glob("submissions/**/*.pdf", recursive=True)

for pdf_path in pdf_paths:
    # Normalize paths
    pdf_path_normalized = pdf_path.replace("\\", "/")
    
    # We will derive names for destination
    parts = pdf_path_normalized.split("/")
    student_id = parts[1] # e.g. '01-chaiklang'
    pdf_name = parts[-1]
    
    dest_pdf_name = f"{student_id}_{pdf_name}"
    dest_pdf_path = os.path.join(books_dest_dir, dest_pdf_name)
    
    # Copy PDF
    print(f"Copying {pdf_path_normalized} -> {dest_pdf_path}")
    shutil.copy2(pdf_path_normalized, dest_pdf_path)
    
    # Check if we have manual metadata for this path
    meta = metadata_map.get(pdf_path_normalized)
    if not meta:
        # Fallback search for metadata or search key
        # Try finding key that ends with parts[-1] and contains student_id
        for k, v in metadata_map.items():
            if student_id in k and pdf_name in k:
                meta = v
                break
                
    if not meta:
        # Generic fallback if not found in metadata_map
        meta = {
            "title": pdf_name.replace(".pdf", "").replace("-", " ").title(),
            "oracle": f"{student_id} Oracle",
            "story": f"เอกสารบันทึกการเรียนรู้และการพัฒนา Workshop 04 - {pdf_name}",
            "treasure": "การทดลองและรัน WebAssembly บนชิป ESP32 ร่วมกับระบบไฟล์ LittleFS คอร์ดีคอดเดอร์ภาพและการเชื่อมโยงข้อมูล",
            "cover": None
        }
        
    # Copy Cover
    cover_src = meta.get("cover")
    dest_cover_name = None
    dest_cover_path = None
    
    if cover_src and os.path.exists(cover_src):
        cover_ext = os.path.splitext(cover_src)[1]
        dest_cover_name = f"{student_id}_{os.path.basename(cover_src)}"
        dest_cover_path = os.path.join(covers_dest_dir, dest_cover_name)
        print(f"Copying cover {cover_src} -> {dest_cover_path}")
        shutil.copy2(cover_src, dest_cover_path)
    else:
        # Try auto-detecting a cover image in the same directory as the pdf
        pdf_dir = os.path.dirname(pdf_path_normalized)
        possible_covers = glob.glob(os.path.join(pdf_dir, "*cover*")) + glob.glob(os.path.join(pdf_dir, "cover*"))
        if possible_covers:
            # Pick first
            chosen_cover = possible_covers[0].replace("\\", "/")
            cover_ext = os.path.splitext(chosen_cover)[1]
            dest_cover_name = f"{student_id}_{os.path.basename(chosen_cover)}"
            dest_cover_path = os.path.join(covers_dest_dir, dest_cover_name)
            print(f"Auto-detected cover {chosen_cover} -> {dest_cover_path}")
            shutil.copy2(chosen_cover, dest_cover_path)
        else:
            print(f"No cover found for {pdf_path_normalized}")
            
    books_db.append({
        "id": f"{student_id}_{pdf_name.replace('.pdf', '')}",
        "oracle": meta["oracle"],
        "author_id": student_id,
        "title": meta["title"],
        "pdf": f"books/{dest_pdf_name}",
        "cover": f"covers/{dest_cover_name}" if dest_cover_name else None,
        "story": meta["story"],
        "treasure": meta["treasure"]
    })

# Save the json database
with open(os.path.join(docs_dir, "classmates-books.json"), "w", encoding="utf-8") as f:
    json.dump(books_db, f, indent=2, ensure_ascii=False)

print(f"Generated {os.path.join(docs_dir, 'classmates-books.json')} with {len(books_db)} books.")
