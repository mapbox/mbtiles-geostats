:warning: **This library is a proof of concept and not under active development!** :warning:

# MBTiles Geostats

Generate a tilestats/geostats JSON object from a series of Mapbox Vector Tile gzipped buffers.

# API

## MBTilesGeostats

Create an mbtiles geostats class

**Examples**

```javascript
var MBTilesGeostats = require('@mapbox/mbtiles-geostats');
var mbs = new MBTilesGeostats();
```

### addBuffer

Add a buffer to the stats object

**Parameters**

-   `buffer` **[Buffer](https://nodejs.org/api/buffer.html)** a gzipped buffer representing a Mapbox Vector Tile

**Examples**

```javascript
var MBS = require('@mapbox/mbtiles-geostats').MBTilesGeostats;
var mbs = new MBS();
buffers.forEach(function(buffer) {
  mbs.addBuffer(buffer);
});
```
