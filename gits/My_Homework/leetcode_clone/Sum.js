function Sum (a,b) {
    return parseInt(a) + parseInt(b)
}
const fs = require('fs');

try {
  fs.writeFileSync('/home/ar/Desktop/leetcode_clone/result.txt', Sum(process.argv[2],process.argv[3]));
  // file written successfully
} catch (err) {
  console.error(err);
}
