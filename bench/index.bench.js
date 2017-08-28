'use strict';

const argv = require('minimist')(process.argv.slice(2));
if (!argv.iterations || !argv.concurrency) {
  console.error('Please provide desired iterations, concurrency');
  console.error('Example: \nnode bench/hello_async.bench.js --iterations 50 --concurrency 10');
  process.exit(1);
}

process.env.UV_THREADPOOL_SIZE = argv.concurrency;

const fs = require('fs');
const path = require('path');
const assert = require('assert')
const d3_queue = require('d3-queue');
const MBS = require('../lib/index.js');
const mbs = new MBS();
let runs = 0;

// more benchmark code ...
