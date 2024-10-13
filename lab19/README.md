## Лабораторная работа 19 "Сборка ядра для ARM"

* Сначала установим необходимые зависимости:
```bash
sudo apt install gcc-arm-linux-gnueabihf aemu-system -y
```

* Заменим значение EXTRAVERSION для выделения "нашей" конфигурации
```Makefile
EXTRAVERSION = -LAB17ARM
```

* В распакованной папке соберём дефолтную конифгурацию
```bash
ARCH=arm make defcofnig
```
Получаем сообщение:
```
*** Default configuration is based on 'multi_v7_defconfig'
```


* Запустим сборку сжатого ядра на 4 потоках 
```bash
ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- make -j4 bzImage
```

* Запустим сборку .dtb 
```bash
ARCH=arm make dtbs
```

* Копируем в папку (из этой папки) run-qemu сжатое ядро и файл DTB
```bash
cp ../linux-5.15-rc1/arch/arm/boot/zImage .
cp ../linux-5.15-rc1/arch/arm/boot/dts/vexpress-v2p-ca9.dtb .
```

* Запустим эмулятор QEMU (с выводом в текущий терминал и отключенным звуком)
```bash
QEMU_AUDIO_DRV=none qemu-system-arm -M vexpress-a9 -kernel zImage -dtb vexpress-v2p-ca9.dtb -append "console=ttyAMA0" -nographic
```

Т.к. отсутствует корневая файловая система, получаем kernel panic:
```
[    4.399493] Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0)
```

> **_NOTE:_**  Для выхода из QEMU: "killall -9 qemu-system-arm"
