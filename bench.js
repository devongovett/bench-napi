let binding = require('node-gyp-build')(__dirname);

console.time('napi');
binding.test();
console.timeEnd('napi');

console.time('v8 tmpl');
binding.tmpl();
console.timeEnd('v8 tmpl');

console.time('js');
let arr = [];
for (let i = 0; i < 100000; i++) {
  arr.push({
    foo: i,
    bar: 'hi'
  });
}
console.timeEnd('js');
