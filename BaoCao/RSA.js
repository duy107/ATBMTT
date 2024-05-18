const dig = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-+";
function get(id) {
    return document.getElementById(id);
}
function checkPri(a) {
    if (a < 2) return false;
    for (var i = 2; i <= Math.sqrt(a); i++) {
        if (a % i == 0) return false;
    }
    return true;
}
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
function gcd(a, b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b, a % b);
}
function squareAndMul(x, b, n) {
    var bin = binaryConvert(b);
    var p = 1;
    for (var i = 0; i < bin.length; i++) {
        if (bin[i] === '1') {
            p = p * p;
            p = p % n;
            p = p * x;
            p = p % n;
        } else {
            p = p * p;
            p = p % n;
        }
    }
    return p;
}
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
function oCoLit2(b, n) {
    let ri = n;
    let rin = b;
    let tmpR, tmpT;
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
function createPri() {
    var p = Math.floor(Math.random() * 10000);
    var q = Math.floor(Math.random() * 10000);
    while (!checkPri(p)) {
        p = Math.floor(Math.random() * 10000);
    }
    while (!checkPri(q)) {
        q = Math.floor(Math.random() * 10000);
    }
    var n = p * q;
    get("p").innerHTML = p;
    get("q").innerHTML = q;
    var phiN = (p - 1) * (q - 1);
    var b = Math.floor(Math.random() * 10000);
    while (b <= 1 || b >= phiN || gcd(b, phiN) != 1) {
        b = Math.floor(Math.random() * 10000);
    }
    get("b").innerHTML = b;
    return { p: p, q: q, phiN: phiN, b: b, n: n };
}
function encodeTextToInt(n, b) {
    var c = [];
    var content = get("textClear").value;
    for (var i = 0; i < content.length; i++) {
        var utf_8 = content.codePointAt(i);
        c.push(squareAndMul(utf_8, b, n));
    }
    return c;
}
function convert64(c) {
    var res = [];
    for (var number of c) {
        var tmp = number;
        var tmpRes = "";
        while (tmp > 0) {
            tmpRes = dig[tmp % 64] + tmpRes;
            tmp = Math.floor(tmp / 64);
        }
        res.push(tmpRes);
    }
    return res;
}
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
function encode() {
    var pri = createPri();
    let c = encodeTextToInt(pri.n, pri.b);
    console.log(c);
    get("textCode").value = convert64(c);
}
function transfer() {
    get('textCode2').value = get('textCode').value;
}
function decodeText(b, n, phiN) {
    let res = "";
    let a = oCoLit2(b, phiN);
    let t = get("textCode2").value;
    let c = t.split(",");
    console.log(c);
    let r = convert10(c);
    console.log(r);
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
// read file
function handleFileSelect(event) {
    // Take out the selected file
    const file = event.target.files[0];
    // create object to read content of file
    const reader = new FileReader();
    // cut name file by point
    const fileNameParts = file.name.split('.');
    const fileExtension = fileNameParts[fileNameParts.length - 1].toLowerCase();

    // Nếu phần mở rộng là 'txt', đó là một file văn bản
    if (fileExtension === 'txt') {
        // function to handle evnet
        reader.onload = function (e) {
            // Reading content is saved in variable content
            const content = e.target.result;
            get("textClear").value = content;
        };
        reader.readAsText(file);
    } else {
        alert("Văn bản không đúng định dạng");
        // remove content of input file 
        event.target.value = '';
    }
}
get("inputFile").addEventListener('change', handleFileSelect);
get("inputFile1").addEventListener('change', handleFileSelect);
// convert to INT
function convertStringToInt(P, base) {
    let R = [];
    for (let i = 0; i < P.length; i++) {
        let c = P.charCodeAt(i).toString();
        while (c.length !== base) {
            c = '0' + c;
        }
        R.push(c);
    }
    return R;
}
// save file
function saveTextAsFile() {
    const textToWrite = get('textCode').value;
    const fileNameToSaveAs = 'myfile.txt';

    const blob = new Blob([textToWrite], { type: 'text/plain;charset=utf-8' });
    saveAs(blob, fileNameToSaveAs);
}
// read docx file
function get(id) {
    return document.getElementById(id);
}
function readDocxFile() {
    const fileInput = get('inputFile');
    const file = fileInput.files[0];
    if (!file) {
        alert("Vui lòng chọn một file DOCX để đọc.");
        return;
    }

    const reader = new FileReader();
    reader.readAsArrayBuffer(file);
    reader.onload = function (event) {
        const arrayBuffer = event.target.result;
        mammoth.convertToHtml({ arrayBuffer: arrayBuffer })
            .then(displayResult)
            .catch(function (err) {
                console.log('Lỗi:', err);
            });
    };
}

function displayResult(result) {
    const html = result.value;
    get('textClear').value = html;
}
// function readDocx(file) {
//     var reader = new FileReader();
//     reader.onload = function (e) {
//         mammoth.convertToHtml({ arrayBuffer: e.target.result })
//             .then(displayResult)
//             .catch(err => {
//                 console.error("Error reading docx file:", err);
//             });
//     };
//     reader.readAsArrayBuffer(file);
// }

// function displayResult(result) {
//     document.getElementById('textClear').innerHTML = result.value;
// }

// // Lắng nghe sự kiện khi người dùng chọn file
// document.getElementById('inputFile').addEventListener('change', function (event) {
//     const file = event.target.files[0];
//     readDocx(file);
// });