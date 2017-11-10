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
var devid, data, datasize, dataset='';

app.get('/', function (req, res) {
  res.send("my iot Protocol ready !");
});

app.post('/write/:data', function (req, res) {
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
      recordTime: new Date()
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
    myreadcollection.find({}).limit(Number(_readdatasize)).sort({recordTime: -1}, function(err, docs){
      console.log(JSON.stringify(docs));
      var dataset = '{"dataset":'+ JSON.stringify(docs) +'}';
      res.send(dataset);
    });
  });
}
