const test = require('tape');
const MBTilesGeostats = require('../lib');

test('does the thing', (assert) => {
  const mbs = new MBTilesGeostats();
  console.log(mbs.addBuffer());
  assert.end();
});
