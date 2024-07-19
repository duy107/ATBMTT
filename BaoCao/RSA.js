const dig = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-+";
function get(id) {
    return document.getElementById(id);
}
// kiem tra so nto
function checkPri(a) {
    if (a < 2) return false;
    for (var i = 2; i <= Math.sqrt(a); i++) {
        if (a % i == 0) return false;
    }
    return true;
}
// chuyen he nhi phan
function binaryConvert(a) {
    var tmp = a;
    var bin = "";
    while (a > 0) {
        bin = (a % 2) + bin;
        a = Math.floor(a / 2);
    }
    if (tmp === 0) bin = "000" + bin;
    if (tmp === 1) bin = "00" + bin;
    if (tmp === 3 || tmp === 2) bin = "0" + bin;
    return bin;
}
// tim uoc chung
function gcd(a, b) {
    if (a == 0) return b;
    if (b == 0) return a;
    while (b > 0) {
        var r = a % b;
        a = b;
        b = r;
    }
    return a;
}
// binh phuong va nhan
function squareAndMul(x, b, n) {
    var bin = binaryConvert(b);
    var p = 1;
    for (var i = 0; i < bin.length; i++) {
        p = (p * p) % n;
        if (bin[i] === '1') {
            p = (p * x) % n;
        }
    }
    return p;
}
console.log(squareAndMul(2, 235, 463));
/*
function oCoLit(b, n) {
    let ri = n;
    let rin = b;
    let to = 0;
    let p, tin;
    let tmpTin, tmpQ, tmpRi, tmpRin, tmpP, tmpT;
    let check = false;
    while (rin > 1) {
        p = Math.floor(ri / rin);
        tmpRi = ri;
        ri = rin;
        rin = tmpRi - ri * p;
        if (!check) {
            tin = 1;
            check = true;
        } else {
            tin = tmpT - to * tmpP;
        }
        tmpP = p;
        tmpT = to;
        to = tin;
    }
    tin = tmpT - to * tmpP;
    if(tin < 0) tin = tin + n;
    return tin;
}
*/
// o co lit
/*
function oCoLit2(b, n) {
    let ri = n;
    let rin = b;
    let tmpR, tmpT, tin;
    let ti_1 = 0, ti = 1;
    while (rin > 1) {
        tin = ti_1 - ti * Math.floor(ri / rin);
        tmpR = rin;
        rin = ri - rin * Math.floor(ri / rin);
        ri = tmpR;
        tmpT = ti;
        ti = tin;
        ti_1 = tmpT;
    }
    if (tin < 0) tin = tin + n;
    return tin;
}
*/
// tinh r1^-1 mod r0
function oCoLit3(r0, r1) {
    let q = new Array(1000).fill(0);
    let s = new Array(1000).fill(0);
    let t = new Array(1000).fill(0);
    let n = r0, r2 = -1, i = 0;
    while (r2 !== 0) {
        r2 = r0 % r1;
        q[i + 1] = Math.floor(r0 / r1);
        if (i === 0) {
            s[i] = 1;
            t[i] = 0;
        } else if (i === 1) {
            s[i] = 0;
            t[i] = 1;
        } else {
            s[i] = s[i - 2] - s[i - 1] * q[i - 1];
            t[i] = t[i - 2] - t[i - 1] * q[i - 1];
        }
        r0 = r1; r1 = r2;
        i++;
    }
    s[i] = s[i - 2] - s[i - 1] * q[i - 1];
    t[i] = t[i - 2] - t[i - 1] * q[i - 1];
    if (t[i] < 0) {
        t[i] += n;
    }
    return t[i];
}
//tao so nguyen to ngau nhien
function createPri() {
    var p = Math.floor(Math.random() * 9001) + 1000;
    var q = Math.floor(Math.random() * 9001) + 1000;
    while (!checkPri(p)) {
        p = Math.floor(Math.random() * 9001) + 1000;
    }
    while (!checkPri(q)) {
        q = Math.floor(Math.random() * 9001) + 1000;
    }
    var n = p * q;
    get("p").innerHTML = p;
    get("q").innerHTML = q;
    var phiN = (p - 1) * (q - 1);
    var b = Math.floor(Math.random() * phiN - 2) + 2;
    while (b <= 1 || b >= phiN || gcd(b, phiN) != 1) {
        b = Math.floor(Math.random() * phiN - 2) + 2;
    }
    get("b").innerHTML = b;
    return { p: p, q: q, phiN: phiN, b: b, n: n };
}
// chuyen chuoi da cho ve mang so da ma hoa
function encodeTextToInt(b, n) {
    var c = [];
    var content = get("textClear").value;
    for (var i = 0; i < content.length; i++) {
        var x = content.codePointAt(i);
        c.push(squareAndMul(x, b, n));
    }
    return c;
}
// chuyen mang số đã mã hóa ở trên về hệ 64
// res là bản mã
let temp = [];
function convert64(c) {
    var res = [];
    for (var number of c) {
        var tmpRes = "";
        while (number > 0) {
            tmpRes = dig[number % 64] + tmpRes;
            number = Math.floor(number / 64);
        }
        res.push(tmpRes);
    }
    for (var i = 0; i < res.length; i++) {
        temp.push(res[i]);
    }
    return res;
}
// chuyen he 64 ve he 10
function convert10(c) {
    var res = [];
    for (var str of c) {
        var tmp = 0;
        for (var i = 0; i < str.length; i++) {
            tmp = tmp * 64 + dig.indexOf(str[i]);
        }
        res.push(tmp);
    }
    return res;
}
// ma hoa
function encode() {
    temp = [];
    var pri = createPri();
    let c = encodeTextToInt(pri.b, pri.n); // c : 1 mảng số
    let text = convert64(c);
    let res = "";
    for (var t of text) {
        res += t;
    }
    get("textCode").value = res;
}
// nút chuyển
function transfer() {
    get('textCode2').value = get('textCode').value;
}
// giai ma x  = y^a mod n
// a = b^-1 phi n
function decodeText(b, n, phiN) {
    let res = "";
    let a = oCoLit3(phiN, b);
    let banMa = temp;
    let r = convert10(banMa);
    for (var i = 0; i < r.length; i++) {
        var num = squareAndMul(r[i], a, n);
        res += String.fromCodePoint(num);
    }
    return res;
}
function decode() {
    let p = parseInt(get("p").innerHTML);
    let q = parseInt(get("q").innerHTML);
    let b = parseInt(get("b").innerHTML);
    let n = p * q;
    let phiN = (p - 1) * (q - 1);
    var dText = decodeText(b, n, phiN);
    get("textClear2").value = dText;
}
// read file txt 
function handleFileSelect(event) {
    const file = event.target.files[0];
    // create object to read content of file
    const reader = new FileReader();
    reader.onload = function (e) {
        const content = e.target.result;
        get("textClear").value = content;
    };
    reader.readAsText(file);
}
get("inputFile").addEventListener('change', handleFileSelect);
// read dox file
function readDocx(file) {
    var reader = new FileReader();
    reader.onload = function (e) {
        mammoth.extractRawText({ arrayBuffer: e.target.result })
            .then(result => {
                document.getElementById('textClear').value = result.value;
            })
            .catch(err => {
                console.error("Error reading docx file:", err);
            });
    };
    reader.readAsArrayBuffer(file);
}
document.getElementById('inputFile').addEventListener('change', function (event) {
    const file = event.target.files[0];
    readDocx(file);
});
// save file text
function saveTextAsFile() {
    const textToWrite = get('textCode').value;
    const fileNameToSaveAs = 'myfile.txt';
    const blob = new Blob([textToWrite], { type: 'text/plain;charset=utf-8' });
    saveAs(blob, fileNameToSaveAs);
}
function saveTextAsFile1() {
    const textToWrite = get('textClear2').value;
    const fileNameToSaveAs = 'myfile.txt';
    const blob = new Blob([textToWrite], { type: 'text/plain;charset=utf-8' });
    saveAs(blob, fileNameToSaveAs);
}
// txt
function handleFileSelect1(event) {
    // Take out the selected file
    const file = event.target.files[0];
    // create object to read content of file
    const reader = new FileReader();
    reader.onload = function (e) {
        const content = e.target.result;
        get("textCode2").value = content;
    };
    reader.readAsText(file);
}
get("inputFile1").addEventListener('change', handleFileSelect1);
// docx
function readDocx1(file) {
    var reader = new FileReader();
    reader.onload = function (e) {
        mammoth.extractRawText({ arrayBuffer: e.target.result })
            .then(result => {
                document.getElementById('textCode2').value = result.value;
            })
            .catch(err => {
                console.error("Error reading docx file:", err);
            });
    };
    reader.readAsArrayBuffer(file);
}

// Lắng nghe sự kiện khi người dùng chọn file
document.getElementById('inputFile1').addEventListener('change', function (event) {
    const file = event.target.files[0];
    readDocx1(file);
});