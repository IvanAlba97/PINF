var cgi = require('cgi');
var http = require('http');
var path = require('path');

var script = path.resolve(__dirname, '../enfecha.cgi');

http.createServer( cgi(script) ).listen(8080,"127.0.0.1", ()=>{console.log("server running")});