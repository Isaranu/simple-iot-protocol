/*
app.js สำหรับสร้าง Protocol IoT device.
code.isaranu.com
coder : isaranu
created : 2017.Nov.11
*/

const express = require('express');
const app = express();
var port = 4000;

var mongojs = require('mongojs');
var Promise = require('promise');
var myiotdb = mongojs('myiotdb');
var dhtdb = mongojs('dht');
var devid, data, datasize, dataset='';
var t, h;

app.get('/', function (req, res) {
  res.send("my iot Protocol ready !");
});

app.get('/write/:data', function (req, res) {
  var strParseWriteReq = JSON.stringify(req.params);
  var strWriteReq = JSON.parse(strParseWriteReq);
  data = strWriteReq.data;
  writedata(data, res);
});

app.get('/read/:datasize', function (req, res) {
  var strParseReadReq = JSON.stringify(req.params);
  var strReadReq = JSON.parse(strParseReadReq);
  datasize = strReadReq.datasize;
  readdata(datasize, res);
});

/* For DHT write */
app.get('/writedht/:t/:h', function (req, res) {
  var strParseWriteReq = JSON.stringify(req.params);
  var strWriteReq = JSON.parse(strParseWriteReq);
  t = strWriteReq.t;
  h = strWriteReq.h;
  writeDHT(t, h, res);
});

/* For DHT data read */
app.get('/readdht/:datasize', function (req, res) {
  var strParseReadReq = JSON.stringify(req.params);
  var strReadReq = JSON.parse(strParseReadReq);
  datasize = strReadReq.datasize;
  readDHT(datasize, res);
});

app.listen(port, function () {
  var nodeStartTime = new Date();
  console.log('My IoT protocol running on port ' + port + ' start at ' + nodeStartTime);
});

/* -- ASYNC / AWAIT function -- */

async function writedata(_data, res){
  await writeDataToMongo(_data, res);
}

function writeDataToMongo(_savedata, res){
  return new Promise(function(resolve, reject){
    var mywritecollection = myiotdb.collection('mycollection');
    mywritecollection.insert({
      data: Number(_savedata),
      recordTime: new Date().getTime()
    }, function(err){
      if(err){
        console.log(err);
        res.send(String(err));
      }else {
        console.log('record data ok');
        res.send('record data ok');
      }
    });
  });
}

async function readdata(_datasize, res){
  await readDataFromMongo(_datasize, res);
}

function readDataFromMongo(_readdatasize, res){
  return new Promise(function(resolve,reject){
    var myreadcollection = myiotdb.collection('mycollection');
    myreadcollection.find({}).limit(Number(_readdatasize)).sort({recordTime: 1}, function(err, docs){
      //console.log(JSON.stringify(docs));
      res.jsonp(docs);
    });
  });
}

async function writeDHT(_t, _h, res){
  await writeDHTtoMongo(_t, _h, res);
}

function writeDHTtoMongo(_saveT, _saveH, res){
  return new Promise(function(resolve, reject){
    var dhtwritecollection = dhtdb.collection('dhtcol');
    dhtwritecollection.insert({
      t: Number(_saveT),
      h: Number(_saveH),
      recordTime: new Date().getTime()
    }, function(err){
      if(err){
        console.log(err);
        res.send(String(err));
      }else {
        console.log('record dht data ok');
        res.send('record dht data ok');
      }
    });
  });
}

async function readDHT(_datasize, res){
  await readDHTFromMongo(_datasize, res);
}

function readDHTFromMongo(_readdatasize, res){
  return new Promise(function(resolve,reject){
    var dhtcollection = dhtdb.collection('dhtcol');
    dhtcollection.find({}).limit(Number(_readdatasize)).sort({recordTime: -1}, function(err, docs){
      //console.log(JSON.stringify(docs));
      res.jsonp(docs);
    });
  });
}
