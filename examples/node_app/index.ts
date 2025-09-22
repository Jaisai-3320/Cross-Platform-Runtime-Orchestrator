import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';


function banner(msg: string) {
const line = '-'.repeat(msg.length + 4);
console.log(`\n${line}\n ${msg}\n${line}`);
}


function main() {
banner('Node App Boot');
console.log('process.version =', process.version);
console.log('platform/arch =', process.platform, process.arch);
console.log('cwd =', process.cwd());


// List a few files in CWD
const files = fs.readdirSync(process.cwd());
console.log('files (first 10)=', files.slice(0, 10));


// Write a small temp file to prove fs works
const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'orch-'));
const tmpFile = path.join(tmpDir, 'hello.txt');
fs.writeFileSync(tmpFile, 'hello from orchestrator node app\n', 'utf8');
console.log('temp file =', tmpFile);


// A tiny async scheduling demo
let ticks = 0;
const timer = setInterval(() => {
ticks++;
console.log('tick', ticks);
if (ticks >= 3) {
clearInterval(timer);
console.log('done');
}
}, 250);
}


main();