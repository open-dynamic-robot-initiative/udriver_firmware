Search.setIndex({"docnames": ["build_instructions", "can/can_connection", "can/can_interface", "can/index", "can/led_codes", "index", "motor_alignment", "program_structure_and_frequencies", "spi/index"], "filenames": ["build_instructions.rst", "can/can_connection.rst", "can/can_interface.rst", "can/index.rst", "can/led_codes.rst", "index.rst", "motor_alignment.rst", "program_structure_and_frequencies.rst", "spi/index.rst"], "titles": ["How to Build and Flash the Firmware", "Connecting via CAN", "CAN Communication Protocol", "Firmware for CAN Communication", "LED Blink Codes", "ODRI Firmware for uDriver Boards", "Motor Alignment Calibration", "Program Structure &amp; Frequencies", "Firmware for SPI Communication"], "terms": {"simpli": [0, 2, 7], "clone": 0, "repositori": [0, 7], "includ": [0, 1], "submodul": 0, "git": 0, "recurs": 0, "http": 0, "github": [0, 5], "com": 0, "open": [0, 1, 5], "dynam": 0, "robot": [0, 5, 6], "initi": [0, 1], "udriver_firmwar": 0, "The": [0, 1, 2, 4, 6, 7], "default": [0, 2], "configur": [0, 1, 2], "i": [0, 1, 2, 3, 4, 5, 6, 7, 8], "assum": [0, 1, 6], "antigrav": 0, "4004": 0, "300kv": 0, "motor": [0, 1, 2, 3, 4, 5, 7], "In": [0, 1, 2], "case": [0, 1, 2, 7], "you": [0, 1, 2, 3, 5, 7], "ar": [0, 1, 2, 4, 5, 6, 7], "us": [0, 1, 2, 3, 4, 5, 7], "differ": [0, 1, 2, 5], "chang": [0, 1, 2], "config_f28069m_drv8305": 0, "appropri": 0, "branch": 0, "our": [0, 5], "softwar": [0, 2], "base": [0, 7], "texa": 0, "instrument": 0, "librari": 0, "which": [0, 1, 2], "can": [0, 4, 5, 7], "download": 0, "from": [0, 1, 4], "websit": 0, "we": [0, 1, 2, 4], "made": 0, "some": [0, 1, 2, 4], "modif": 0, "origin": 0, "need": [0, 1, 6, 7], "provid": [0, 2], "patch": 0, "file": [0, 7], "motorware_1_01_00_18_patch": 0, "thei": [0, 1, 2, 4, 6, 7], "directori": 0, "firmware_can": 0, "firmware_spi": 0, "note": [0, 1, 2, 4, 7], "two": [0, 2, 3, 4, 5, 7], "version": [0, 3, 5, 8], "follow": [0, 1, 2, 7], "step": [0, 1], "set": [0, 1, 2, 7], "up": [0, 1], "project": [0, 7], "v1": 0, "01": 0, "00": 0, "18": 0, "extract": 0, "sourc": [0, 5], "For": [0, 1], "linux": 0, "user": 0, "unfortun": 0, "ti": [0, 3], "onli": [0, 1, 2, 4, 7], "window": [0, 4], "There": [0, 1, 2, 5], "realli": 0, "an": [0, 1, 2, 4, 6, 7], "requir": 0, "them": [0, 1], "either": 0, "machin": 0, "emul": 0, "like": [0, 1], "wine": 0, "copi": 0, "search": 0, "contain": [0, 2, 3, 8], "sw": 0, "firmware_x": 0, "where": [0, 6, 7], "x": 0, "spi": [0, 3, 5, 7], "depend": [0, 1, 4], "want": [0, 1, 2, 3, 7], "structur": [0, 2], "should": [0, 1, 2, 4, 7], "thi": [0, 1, 2, 3, 4, 5, 6, 7, 8], "amd_motorware_ext": 0, "add": [0, 8], "here": [0, 1, 2], "doc": 0, "eclips": 0, "mw_explor": 0, "mw_dual_motor_torque_ctrl": 0, "final": 0, "go": [0, 7], "appli": [0, 5, 6], "p1": 0, "motorware_1_01_00_18": 0, "To": [0, 1, 2, 6], "board": [0, 1, 3, 4, 6], "cc": 0, "These": 0, "test": 0, "9": 0, "1": [0, 1, 2, 4, 7], "0": [0, 1, 2], "other": [0, 1, 2, 7], "mai": [0, 1, 2, 4, 6], "work": [0, 1], "well": [0, 1], "when": [0, 1, 2, 3, 4, 5, 6], "make": [0, 6], "sure": [0, 6], "compon": 0, "select": 0, "processor": 0, "support": [0, 1], "c2000": 0, "32": 0, "bit": [0, 1, 6], "real": 0, "time": [0, 1, 4, 6, 7], "mcu": 0, "probe": 0, "xd": 0, "explicitli": [0, 7], "older": 0, "start": [0, 1, 4, 6], "first": [0, 1, 2, 4, 6], "have": [0, 1, 2, 5], "specifi": [0, 2], "workspac": 0, "locat": 0, "just": 0, "store": [0, 2], "its": 0, "relat": [0, 7], "e": [0, 1, 2, 4, 6], "via": [0, 2, 3, 5, 7], "menu": 0, "dialogu": 0, "one": [0, 1, 2, 4, 5], "packag": [0, 1], "discov": 0, "pane": 0, "show": [0, 1, 7], "dual_motor_torque_ctrl_x": 0, "option": 0, "after": [0, 1, 6], "explor": 0, "while": [0, 2, 4, 5, 6, 7], "connect": [0, 2, 3, 4], "comput": [0, 1, 4], "usb": [0, 4], "mostli": 0, "develop": 0, "jtag": 0, "enabl": [0, 1, 2, 4, 6], "see": [0, 1, 2, 4, 5, 7], "below": [0, 2, 4], "compil": 0, "your": 0, "releas": 0, "power": [0, 1, 6], "pc": [0, 2], "all": [0, 1, 2], "three": [0, 4], "upper": 0, "posit": [0, 2, 4, 6, 7], "debugg": 0, "click": 0, "bug": 0, "icon": 0, "tool": 0, "bar": 0, "silicon": 0, "correspond": [0, 1], "button": 0, "press": 0, "resum": 0, "now": [0, 1, 2], "guicompos": 0, "gui": [0, 3, 7], "modifi": 0, "variabl": 0, "express": [0, 1], "view": 0, "quit": 0, "termin": [0, 1], "detach": 0, "stop": 0, "program": [0, 4], "With": 0, "procedur": [0, 1], "perman": 0, "That": 0, "mean": [0, 1, 2, 4], "repeat": [0, 1], "everytim": 0, "restart": 0, "written": [0, 1, 7], "rather": 0, "than": [0, 2], "ram": 0, "so": [0, 1, 2, 4, 6], "type": [0, 1, 2], "same": [0, 2, 4, 5, 6, 7], "describ": [0, 1, 2, 5], "abov": [0, 1, 2, 4, 7], "instead": [0, 3], "monitor": 0, "befor": [0, 2, 6], "right": 0, "automat": [0, 1, 4, 6], "load": [0, 4], "next": [0, 1], "section": [0, 3, 5, 8], "memori": 0, "tell": 0, "hidden": [0, 4], "under": 0, "j1": [0, 4], "boosterpack": [0, 4], "2": [0, 1, 2], "3": [0, 1, 2, 4, 7], "down": [0, 2], "possibl": [0, 6], "updat": [0, 7], "back": 0, "again": [0, 4], "firmwar": [1, 2, 7], "0b": 1, "standard": 1, "theori": 1, "ani": [1, 2, 4, 6, 7], "devic": 1, "abl": 1, "commun": [1, 5], "practic": [1, 2], "successfulli": 1, "pcan": [1, 4], "pci": 1, "dual": [1, 3, 7], "channel": 1, "card": 1, "classic": 1, "peak": 1, "system": [1, 2, 4, 6, 7], "howev": [1, 4], "problem": [1, 4], "": [1, 2], "fd": 1, "recommend": 1, "stick": 1, "non": 1, "manufactur": 1, "cannot": 1, "sai": 1, "anyth": 1, "about": 1, "those": 1, "socketcan": 1, "alreadi": [1, 2], "kernel": 1, "manual": [1, 4, 6], "instal": 1, "each": [1, 2, 7], "avail": 1, "call": [1, 7], "can0": 1, "can1": 1, "can2": 1, "ha": [1, 2, 4, 7], "order": [1, 2], "usabl": [1, 4], "mbit": [1, 2], "sampl": [1, 2], "point": [1, 2], "86": [1, 2], "7": [1, 2], "accordingli": 1, "run": [1, 2, 4, 6, 7], "sudo": 1, "ip": 1, "link": 1, "bitrat": 1, "1000000": 1, "867": 1, "done": [1, 2], "replac": 1, "assign": [1, 2], "seem": 1, "logic": 1, "outsid": 1, "find": [1, 5, 6], "out": [1, 2], "physic": 1, "port": 1, "etc": [1, 2, 4, 7], "nicer": 1, "wai": 1, "do": [1, 2, 4, 6], "precedur": 1, "u": 1, "disconnect": 1, "watch": 1, "netstat": 1, "It": [1, 2], "output": 1, "tabl": [1, 2], "ifac": 1, "mtu": 1, "met": 1, "rx": 1, "ok": 1, "err": 1, "drp": 1, "ovr": 1, "tx": 1, "flg": 1, "16": 1, "oru": 1, "been": 1, "flash": 1, "send": [1, 2, 4], "messag": [1, 4], "list": 1, "valu": [1, 2, 7], "increas": 1, "current": [1, 2, 4, 6, 7], "until": [1, 4], "identifi": [1, 2], "put": 1, "label": 1, "As": [1, 2], "long": [1, 2], "map": 1, "fix": [1, 2], "ad": [1, 2], "more": [1, 4], "remov": 1, "exist": 1, "ones": 1, "identif": 1, "basic": [1, 5], "consol": 1, "applic": 1, "candump": 1, "cansend": 1, "On": [1, 4], "ubuntu": 1, "util": 1, "adjust": 1, "command": [1, 4], "displai": 1, "id": [1, 2], "010": 1, "onc": [1, 3], "everi": [1, 7], "second": [1, 4, 6, 7], "statu": [1, 4], "If": [1, 2, 3, 5], "don": [1, 2], "t": [1, 2], "someth": 1, "wrong": 1, "proce": 1, "separ": 1, "keep": [1, 2], "execut": [1, 7], "005": 1, "0000000000000000": 1, "target": 1, "zero": [1, 2], "000": 1, "000000000000001e": 1, "disabl": [1, 2, 4], "receiv": [1, 4], "timeout": 1, "0000000100000001": 1, "0000000100000014": 1, "measur": 1, "0000000100000002": 1, "0000000100000003": 1, "020": 1, "030": 1, "040": 1, "050": 1, "high": [1, 2], "frequenc": 1, "jitter": 1, "held": [1, 6], "place": [1, 6], "few": [1, 2, 4, 6], "actual": 1, "calibr": [1, 4], "perform": 1, "align": [1, 2, 4], "everyth": [1, 7], "behav": [1, 7], "gener": 1, "addit": [1, 2, 4], "check": [1, 2], "rate": [1, 2], "stabl": 1, "d": 1, "fff": 1, "print": 1, "row": 1, "pass": 1, "between": [1, 6], "previou": [1, 2], "close": 1, "001": 1, "m": 1, "littl": [1, 6], "deviat": 1, "larger": 1, "delai": 1, "indic": [1, 4], "instabl": 1, "whether": 1, "control": [1, 2, 3, 6, 7], "less": 1, "frame": 2, "11": 2, "distinguish": 2, "data": 2, "how": 2, "insid": 2, "also": [2, 4, 6], "defin": 2, "prioriti": 2, "node": 2, "try": 2, "lower": 2, "come": 2, "8": 2, "byte": 2, "split": 2, "higher": [2, 6], "part": [2, 7], "4": [2, 4], "name": 2, "modul": 2, "refer": 2, "mdl": 2, "mdh": 2, "size": 2, "0x010": 2, "0x020": 2, "i_q": 2, "both": [2, 4, 5], "0x030": 2, "encod": [2, 4, 6], "0x040": 2, "veloc": 2, "0x050": 2, "adc": 2, "input": 2, "g": [2, 4, 6], "potentiomet": 2, "sensor": 2, "read": 2, "a6": 2, "b6": 2, "0x060": 2, "index": 2, "whenev": 2, "detect": 2, "5": 2, "tick": 2, "q24": 2, "divid": 2, "24": 2, "get": 2, "float": 2, "represent": 2, "0x100": 2, "0x101": 2, "optoforc": 2, "thing": 2, "simpl": 2, "reconfigur": 2, "flag": 2, "readi": [2, 4], "A": 2, "process": [2, 4, 6], "finish": [2, 7], "No": 2, "critic": [2, 7], "temperatur": 2, "unus": 2, "convert": 2, "rollov": 2, "exceed": 2, "max": 2, "enable_pos_rollover_error": 2, "free": 2, "won": 2, "sens": 2, "might": 2, "futur": 2, "reserv": 2, "though": [2, 7], "far": 2, "unit": 2, "0x000": 2, "can_id_command": 2, "0x005": 2, "can_id_iqref": 2, "iqref": 2, "mrev": 2, "revolut": 2, "half": 2, "full": [2, 7], "pleas": [2, 7], "multipli": 2, "round": 2, "integ": 2, "consist": [2, 7], "associ": 2, "specif": [2, 3, 8], "paramet": 2, "0x01": 2, "enable_si": 2, "0x02": 2, "enable_mtr1": 2, "0x03": 2, "enable_mtr2": 2, "0x04": 2, "enable_vspring1": 2, "virtual": 2, "spring": 2, "mode": 2, "0x05": 2, "enable_vspring2": 2, "0x0c": 2, "send_curr": 2, "0x0d": 2, "send_posit": 2, "0x0e": 2, "send_veloc": 2, "0x0f": 2, "send_adc6": 2, "0x14": 2, "send_al": 2, "0x1e": 2, "set_can_recv_timeout": 2, "millisecond": 2, "uint32": 2, "0x1f": 2, "exampl": [2, 7], "nomenclatur": 2, "document": [2, 5, 7, 8], "embed": 2, "secur": 2, "featur": 2, "interrupt": [2, 7], "exit": 2, "without": [2, 7], "properli": 2, "shut": 2, "sinc": [2, 7], "last": 2, "wa": [2, 7], "rais": 2, "exce": 2, "durat": 2, "greater": 2, "consequ": 2, "kept": 2, "mind": 2, "otherwis": 2, "trigger": [2, 7], "immedi": 2, "good": 2, "anywai": [2, 7], "clear": 2, "potenti": 2, "danger": 2, "loop": [2, 7], "even": 2, "okai": 2, "dure": 2, "intial": 2, "reenabl": 2, "inform": [3, 4, 7, 8], "allow": 3, "torqu": [3, 6], "launchpad": [3, 4], "evalu": 3, "blmc": 3, "\u00b5driver": 3, "ethernet": 3, "master": [3, 5], "univers": 3, "protocol": 3, "led": 3, "blink": 3, "code": [3, 7], "itself": 4, "therefor": [4, 7], "gpio": 4, "12": 4, "13": 4, "22": 4, "3v": 4, "pin": 4, "synchron": 4, "extern": [4, 6], "visual": 4, "import": 4, "state": 4, "off": [4, 6], "slow": 4, "hz": 4, "least": 4, "fast": 4, "yet": 4, "lock": 4, "move": [4, 6], "ignor": 4, "take": 4, "sent": 4, "acknowledg": 4, "cabl": 4, "plug": 4, "driver": 4, "turn": 4, "soon": 4, "fail": 4, "unstabl": 4, "error": 4, "occur": 4, "descript": 4, "usual": [4, 7], "prevent": 4, "being": 4, "re": 4, "resolv": 4, "actuat": 5, "latter": 5, "through": 5, "detail": [5, 7], "principl": 5, "page": [5, 7], "question": 5, "forum": 5, "offset": 6, "rotor": 6, "accur": 6, "field": 6, "orient": 6, "At": 6, "begin": 6, "achiev": 6, "best": 6, "accuraci": 6, "block": 6, "becaus": 6, "push": 6, "against": 6, "obstacl": 6, "avoid": [6, 7], "gravit": 6, "pull": 6, "joint": 6, "minim": 6, "what": 6, "happen": 6, "inaccur": 6, "better": 6, "effici": 6, "complet": 6, "still": 6, "doe": 7, "regard": 7, "intend": 7, "peopl": 7, "who": 7, "modifii": 7, "microcontrol": 7, "endless": 7, "main": 7, "function": 7, "guarante": 7, "isr": 7, "servic": 7, "routin": 7, "pwm": 7, "stuff": 7, "must": 7, "withing": 7, "f": 7, "miss": 7, "decim": 7, "reduc": 7, "relev": 7, "n": 7, "th": 7, "figur": 7, "illustr": 7, "hierach": 7, "fraction": 7, "remain": 7, "ctrl": 7, "lab": 7, "implement": 7, "cleanli": 7, "pi": 7, "implicitli": 7, "mention": 7, "minor": 7, "issu": 7, "singl": 7, "45": 7, "khz": 7, "20": 7, "15": 7, "10": 7, "posconv": 7, "speed": 7, "factor": 7, "user_jx": 7, "h": 7, "user_mtr_on_jx": 7, "config": 7, "simplifi": 7}, "objects": {}, "objtypes": {}, "objnames": {}, "titleterms": {"how": 0, "build": 0, "flash": 0, "firmwar": [0, 3, 5, 8], "get": 0, "code": [0, 2, 4], "motorwar": 0, "instal": 0, "compos": 0, "studio": 0, "instruct": 0, "import": 0, "run": 0, "debug": 0, "mode": 0, "write": 0, "launchpad": 0, "boot": 0, "switch": 0, "connect": 1, "via": 1, "can": [1, 2, 3], "hardwar": 1, "linux": 1, "driver": 1, "setup": 1, "determin": 1, "name": 1, "interfac": 1, "test": 1, "commun": [2, 3, 8], "protocol": 2, "bit": 2, "time": 2, "messag": 2, "sent": 2, "from": 2, "board": [2, 5], "statu": 2, "error": 2, "command": 2, "receiv": 2, "timeout": 2, "content": 3, "led": 4, "blink": 4, "green": 4, "blue": 4, "yellow": 4, "red": 4, "odri": 5, "udriv": 5, "link": 5, "motor": 6, "align": 6, "calibr": 6, "program": 7, "structur": 7, "frequenc": 7, "todo": [7, 8], "configur": 7, "flow": 7, "spi": 8}, "envversion": {"sphinx.domains.c": 2, "sphinx.domains.changeset": 1, "sphinx.domains.citation": 1, "sphinx.domains.cpp": 6, "sphinx.domains.index": 1, "sphinx.domains.javascript": 2, "sphinx.domains.math": 2, "sphinx.domains.python": 3, "sphinx.domains.rst": 2, "sphinx.domains.std": 2, "sphinx.ext.intersphinx": 1, "sphinx.ext.todo": 2, "sphinx": 56}})