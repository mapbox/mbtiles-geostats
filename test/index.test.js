const test = require('tape');
const MBTilesGeostats = require('../lib');

test('[addBuffer] fails when used incorrectly', (assert) => {
  const mbs = new MBTilesGeostats();

  try {
    mbs.addBuffer();
    assert.fail();
  } catch (err) {
    assert.equal(err.message, 'No value passed into \"addBuffer\"', 'expected error message');
  }

  try {
    mbs.addBuffer(15);
    assert.fail();
  } catch (err) {
    assert.equal(err.message, 'Value passed into \"addBuffer\" is not a buffer', 'expected error message');
  }

  assert.end();
});

test('[addBuffer] fails with an invalid vector tile', (assert) => {
  const mbs = new MBTilesGeostats();

  try {
    mbs.addBuffer(new Buffer('I am not a vector tile'));
    assert.fail();
  } catch (err) {
    assert.equal(err.message, 'Buffer is not a valid Mapbox Vector Tile', 'expected error message');
  }

  assert.end();
});
