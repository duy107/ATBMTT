const crypto = require('crypto');
const bigInt = require('big-integer');

// Hàm tạo số nguyên tố có số bit xác định
function generatePrime(bits) {
    let prime = bigInt(0);
    while (!prime.isPrime()) {
        prime = bigInt.randBetween(bigInt(2).pow(bits - 1), bigInt(2).pow(bits).prev());
    }
    return prime;
}

// Tạo số ngẫu nhiên trong khoảng [min, max]
function randomBigIntInRange(min, max) {
    const range = max.subtract(min);
    const randomNumber = bigInt.randBetween(bigInt(0), range);
    return randomNumber.add(min);
}

// Hàm bình phương và nhân
function squareAndMultiply(base, exponent, modulus) {
    let result = bigInt(1);
    let baseValue = base.mod(modulus);

    while (exponent.gt(0)) {
        if (exponent.and(1).eq(1)) {
            result = result.multiply(baseValue).mod(modulus);
        }
        baseValue = baseValue.square().mod(modulus);
        exponent = exponent.shiftRight(1);
    }

    return result;
}

// Tạo khóa
let q = generatePrime(160);
console.log("Số nguyên tố q có 160 bit:", q.toString());

let z = bigInt("2497460329000917895579345565643298857934058559076088451079739924468092334190540960797321587701045374701498231496839337800047993903793932694065955797084319110393930014167003359000649130117077736431082768");

let p = q.multiply(z).add(1);
while (!p.isPrime()) {
    q = generatePrime(160);
    p = q.multiply(z).add(1);
}
console.log("Số nguyên tố q có 160 bit:", q.toString());
console.log("p", p.toString());
console.log(p.bitLength().toString());

let h = randomBigIntInRange(1, p.subtract(1));
console.log("h", h.toString());

let g = squareAndMultiply(h, z, p);
console.log("g", g.toString());
while (g.compare(1) <= 0) {
    h = randomBigIntInRange(1, p.subtract(1));
    console.log("h", h.toString());
    g = squareAndMultiply(h, z, p);
    console.log("g", g.toString());
}

let x = randomBigIntInRange(1, q.subtract(1));
console.log("x", x.toString());

let y = squareAndMultiply(g, x, p);
console.log("y ", y.toString());

// Tạo thông điệp và tính hàm băm SHA-1 của thông điệp
let message = "chiểu đớ";
let hash = crypto.createHash('sha1').update(message).digest('hex');
let hashInt = bigInt(hash, 16);
console.log("SHA-1(m):", hashInt.toString());

// Ký thông điệp
let k, r, s;
do {
    k = randomBigIntInRange(1, q.subtract(1));
    console.log("k ", k.toString());

    r = squareAndMultiply(g, k, p).mod(q);
    console.log("r", r.toString());

    let kInv = k.modInv(q);
    s = kInv.multiply(hashInt.add(x.multiply(r))).mod(q);
    console.log("s", s.toString());
} while (r.isZero() || s.isZero());

console.log("Chữ ký số:");
console.log("r:", r.toString());
console.log("s:", s.toString());

// Xác nhận chữ ký
function verifySignature(message, r, s, p, q, g, y) {
    if (r.compare(0) <= 0 || r.compare(q) >= 0 || s.compare(0) <= 0 || s.compare(q) >= 0) {
        return false;
    }

    let hash = crypto.createHash('sha1').update(message).digest('hex');
    let hashInt = bigInt(hash, 16);
    console.log("SHA-1(m):", hashInt.toString());

    let w = s.modInv(q);
    let u1 = hashInt.multiply(w).mod(q);
    let u2 = r.multiply(w).mod(q);

    let v = squareAndMultiply(g, u1, p).multiply(squareAndMultiply(y, u2, p)).mod(p).mod(q);

    console.log("w:", w.toString());
    console.log("u1:", u1.toString());
    console.log("u2:", u2.toString());
    console.log("v:", v.toString());

    return v.equals(r);
}

let isValid = verifySignature(message, r, s, p, q, g, y);
console.log("Chữ ký hợp lệ:", isValid);
