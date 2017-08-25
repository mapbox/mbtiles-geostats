# MBTiles Geostats

Generate a geostats JSON object from a series of Mapbox Vector Tile gzipped buffers.

:warning: **This library under development! Please expect breaking API changes prior to a 1.x release.** :warning:

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
