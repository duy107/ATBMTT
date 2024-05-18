const form1 = document.querySelector("#form1");
const form2 = document.querySelector("#form2");
const form3 = document.querySelector("#form3");
const next1 = document.querySelector("#next1");
const next2 = document.querySelector("#next2");
const back1 = document.querySelector("#back1");
const back2 = document.querySelector("#back2");
const random = document.querySelector("#random");
const taoKhoa = document.querySelector("#crekey");
const ktra = document.querySelector("#ktra");
const ky = document.querySelector("#ky");
const hien = document.querySelector(".btnh");
const an = document.querySelector(".btna");



next1.addEventListener("click", function(){
    form1.style.left = "-550px";
    form2.style.left = "80px";
});

next2.addEventListener("click", function(){
    form2.style.left = "-550px";
    form3.style.left = "80px";
});

back1.addEventListener("click", function(){
    form2.style.left = "550px";
    form1.style.left = "80px";
});

back2.addEventListener("click", function(){
    form3.style.left = "550px";
    form2.style.left = "80px";
});

//random


function checkPri(num){
    if(num < 2) return false;
    for(let i = 2; i <= Math.sqrt(num); i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
};

function checkP(nump){
    var check = true;
    if(!checkPri(nump)){
        check = false;
    }
    return check;
};

function oClit (k, p) {
    let ri = p;
    let rin = k;
    let tst = 0, ts = 1;
    let tin;
    let tmp;
    let gtmp;
    while(rin > 1){
        tin = tst - ts*Math.floor(ri / rin);
         tmp = rin;
        rin = ri - rin*Math.floor(ri / rin);
        ri = tmp;
        gtmp = ts;
        ts = tin;
        tst = gtmp;
    }
    if(tin < 0){
        tin = tin + p;
    }
    return tin;
};


    
random.addEventListener("click", function(){
    let alpha = document.querySelector("#numl").value;
    alpha = Math.floor(Math.random() * 10000);
    document.querySelector("#numl").value = alpha;
});

random.addEventListener("click", function(){
    let x = document.querySelector("#numx").value;
    x = Math.floor(Math.random() * 1000000);
    document.querySelector("#numx").value = x;
});

random.addEventListener("click", function(){
    var p = Math.floor(Math.random() * 10000);
    var k = Math.floor(Math.random() * 10000);
    while(!checkPri(p)){
        p = Math.floor(Math.random() * 10000);
    }
    while(gCD(k, (p - 1)) != 1){
        k = Math.floor(Math.random() * p) - 2;
    }
    var a = Math.floor(Math.random() * p) - 2;
    document.querySelector("#numa").value = a;
    document.querySelector("#nump").value = p;
    document.querySelector("#numk").value = k;
});

function checkMess() {  
    var fileInput = document.querySelector("#file1");
    var file = fileInput.files[0]; 
    var mes = document.querySelector("#mess").value;
    var check = true;
    if(!file && mes ==''){
        check = false;
    };
    return check;
}

function gCD(p, k) {  
    let du = 1;
    while(du != 0){
        du = p % k;
        p = k;
        k = du;
    }
    return p;
};

function chuyenNhiPhan(decimal){
    if (decimal === 0) {
        return '0';
    }
    let binary = '';
    while (decimal > 0) {
        binary = (decimal % 2) + binary;
        decimal = Math.floor(decimal / 2);
    }
    return binary;
};



function binhPhuongVoiNhan(num, x, y) {
    const tinh = chuyenNhiPhan(num);
    // console.log(tinh[0]);
    let p = 1;
    for(let i = 0; i < tinh.length; i++){
        if(tinh[i] == 1){
            p = p * p;
            p = p % y;
            p = p * x;
            p = p % y;
        }
        else{
            p = p * p;
            p = p % y;
        }
    }
    return p;
};

// console.log(binhPhuongVoiNhan(25, 235, 29));

function testInputtk(){
    const soP = parseInt(document.querySelector("#nump").value);
    const soAlpha = parseInt(document.querySelector("#numl").value);
    const soA = parseInt(document.querySelector("#numa").value);
    var check = true;
    if(isNaN(soA) || isNaN(soAlpha) || isNaN(soP)){
        check = false;
    };
    return check;
};

function testInputky(){
    const soK = parseInt(document.querySelector("#numk").value);
    const x = parseInt(document.querySelector("#numx").value);
    var check = true;
    if(isNaN(soK)){
        check = false;
    };
    return check;
};
taoKhoa.addEventListener('click', function(){
    var a = document.querySelector("#numa").value;
    var p = document.querySelector("#nump").value;
    var al = document.querySelector("#numl").value;
    if(!checkP(p)){
        alert("Số P phải là SNT !!!");
        return 0;
    }
    if(!testInputky()){
        alert("Vui lòng nhập đủ dữ liệu!!");
        return 0;
    };
    checkP();
    var result = binhPhuongVoiNhan(a, al, p);
    document.querySelector("#Kpub").innerHTML = "Key pulic: {" + a + ";  " + al + ";  " + result + "}";
    document.querySelector("#Kpr").innerHTML = "Key private: **********";
    document.getElementById('betal').innerHTML = "Beta: "+ result;

//     console.log(tinhKtra(112));

// console.log(tinhXicma(112, 463));
});

an.addEventListener('click', function(){
    an.classList.add('an');
    document.querySelector("#Kpr").innerHTML = "Key private: **********";
});
hien.addEventListener('click', function(){
    var a = document.querySelector("#numa").value;
    an.classList.remove('an');
    document.querySelector("#Kpr").innerHTML = "Key private: " + a;
    
});


function readFile(file, callback) {
    var reader = new FileReader(); 
    reader.onload = function(event) { 
        var content = event.target.result; 
        callback(content); 
    }; 
    reader.readAsText(file); 
}
var textMes = '';
// ky
ky.addEventListener('click', function () { 
    const soP = parseInt(document.querySelector("#nump").value);
    var fileInput = document.querySelector("#file1");
    var file = fileInput.files[0]; 
    if (file) {
        readFile(file, function(content) {
            console.log(content);
            var x = (convert(content));
            console.log("Giá trị của x sau khi đọc file:", x);
            textMes = x;
            tinhXicma(x, soP);
        });
    }

    else if(document.querySelector("#mess").value == ''){
        var x = parseInt(document.querySelector("#numx").value) ; 
        console.log("Giá trị của x:", x);
        tinhXicma(x, soP);
    }
    else{
        var x = (convert(document.querySelector("#mess").value)) ; 
        console.log("Giá trị của x:", x);
        textMes = x;
        tinhXicma(x, soP);
    };
    console.log(textMes);
});

console.log(textMes);


function tinhXicma(x, soP){
    const soAlpha = parseInt(document.querySelector("#numl").value);
    const soA = parseInt(document.querySelector("#numa").value);
    const soK = parseInt(document.querySelector("#numk").value);

    if(!checkP(soP)){
        alert("Số P phải là SNT !!!");
        return 0;
    }
    if(!testInputky()){
        alert("Vui lòng nhập đủ dữ liệu!!");
        return 0;
    };

    if(!checkMess()){
        alert("Vui lòng nhập vào tin nhắn!!!");
        return 0;
    };

    const res = oClit(soK, (soP - 1));
    const gama = binhPhuongVoiNhan(soK, soAlpha, soP);
    document.querySelector("#gamal1").value = gama;

    
    const h = 5;
    var verc = [];
    var chuky2 = [];
    for(let i = 0; i < x.length; i += h){
        verc.push(x.substring(i, i + h));
    };
    console.log(verc);

    for(let i = 0; i < verc.length; i++){
        const res2 = (parseInt(verc[i])  - soA * gama)%(soP - 1);
        let result = (res2*res) % (soP - 1);
        if(result < 0){
            result = result + (soP - 1);
        };
        // chuKy.push(result);
        chuky2.push(result);
    };


    let re = '';
    for(let i = 0; i < chuky2.length; i++){
        re += chuky2[i];
    };


    document.querySelector("#xicmal1").value = re;
    document.querySelector("#gamal").innerHTML = "Gamal: " + gama;
    document.querySelector("#xicmal").innerHTML = "Xicmal: " + re;
    if(re =='' || !isNaN(gama)){
        alert("Ký thành công!");
    }
};

function convert(text) {  
    let st = '';
    for(let i = 0; i < text.length; i++){
        st += text.charCodeAt(i).toString(10);
    }
    return st;
};

ktra.addEventListener('click', function () { 
    var fileInput = document.querySelector("#file2");
    var file = fileInput.files[0]; 
    if (file) {
        readFile(file, function(content) {
            var xmes = (convert(content)) ; 
            console.log("Giá trị của xmes sau khi đọc file la:", xmes);
            tinhKtra(xmes);
        });
    }

    else{
        var xmes = (convert(document.querySelector("#mess1").value)) ; 
        console.log("Giá trị của xmes:", xmes);
        tinhKtra(xmes);
    }
    
});

function tinhKtra(xmes){
    console.log(textMes);
    if(!checkMess()){
        alert("Vui lòng nhập vào tin nhắn!!!");
        return 0;
    };
    const soP = parseInt(document.querySelector("#nump").value);
    const soAlpha = parseInt(document.querySelector("#numl").value);
    const soA = parseInt(document.querySelector("#numa").value);
    const soK = parseInt(document.querySelector("#numk").value);
    const gama = document.querySelector("#gamal1").value;
    // const res2 = (x - soA * gama)%(soP - 1);
    // let result = (res2*res) % (soP - 1);
    // if(result < 0){
    //     result = result + (soP - 1);
    // }

    //xicmal
    const h = 5;
    var verc = [];
    var chuky2 = [];
    for(let i = 0; i < textMes.length; i += h){
        verc.push(textMes.substring(i, i + h));
    };
    console.log(verc);
    const res = oClit(soK, (soP - 1));
    for(let i = 0; i < verc.length; i++){
        const res2 = (parseInt(verc[i])  - soA * gama)%(soP - 1);
        let result = (res2*res) % (soP - 1);
        if(result < 0){
            result = result + (soP - 1);
        };
        chuky2.push(result);
    };
    //end xicmal

    const xicma = document.querySelector("#xicmal1").value;


    var beta = binhPhuongVoiNhan(soA, soAlpha, soP);

    var end1 = [];
    var end2 = [];
    for(let i = 0; i < chuky2.length; i++){
        const kq = binhPhuongVoiNhan(gama, beta, soP);
        const kq2 =  binhPhuongVoiNhan(parseInt(chuky2[i]), gama, soP);
        // console.log(kq);
        // console.log(kq2);
        let endres = (kq * kq2) % soP;
        // console.log(endres);
        end1.push(endres);
    };


    //xmes
    var verc2 = [];
    for(let i = 0; i < xmes.length; i += h){
        verc2.push(xmes.substring(i, i + h));
    };
    console.log(verc2);
    for(let i = 0; i < verc2.length; i++){
        let endres2 = binhPhuongVoiNhan(parseInt(verc2[i]), soAlpha, soP);
        end2.push(endres2);
    };

    console.log(end1);
    console.log(end2);

    let consmax = 0;
    if(end1.length < end2.length){
        consmax = end2.length;
    }
    else{
        consmax = end1.length;
    }
    console.log(consmax);
    let ind = 0;
    var checkm = true;
    var Result = true;
    for(let i = 0; i < consmax; i++){
        if(end1[i] != end2[i]){
            Result = false;
            checkm = false;
        };
    }
    
    // console.log(xmes);

    document.querySelector("#betal1").innerHTML ="Beta: " + beta;
    document.querySelector("#gamal1").innerHTML ="Gamal: " + gama;
    document.querySelector("#numal1").innerHTML = "Alpha: " + soAlpha;
    document.querySelector("#xicmal1").innerHTML ="Xicma: " + xicma;
        
    if(checkm){
        alert("Văn bản chưa bị sửa đổi.");
    }
    else{
        alert("Văn bản đã bị sửa đổi.");
    };
};
