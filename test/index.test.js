const test = require('tape');
const MBS = require('../lib');

test('does the thing', (assert) => {
  const mbs = new MBS.MBTilesGeostats();
  console.log(mbs.addBuffer());
  assert.end();
});
