var elasticsearch = require ('elasticsearch');
var fs = require('fs');

var client = new elasticsearch.Client();

var indexName = "platerecognition";

function init(client) {
	client.search({index:indexName, body:{"query":{"match_all":{}}}}).then(
		function (resp){
			console.log("Info : All is ok");
		},
		function (error){
			console.log("Error : Index " + indexName + " missing.");
			console.log("Info : Creating " + indexName + ".");
			client.indices.create({index:"users"},
			function(resp) {
				console.log("Info : Index " + indexName + " created.");
			},
			function (error){
				console.log("Error :  unable to create new index");
			});
		}
	);
}
// TODO remove init from here
init(client);


function newPlate(path, resReq){
	client.index({
		index:indexName,
		type:'plate',
		body:{
			'status':'new',
		}
	}).then(
		function(resp){
			console.log(resp);
			savePlateFile("origin", resp._id, path);
			resReq.json({message:"New plate Added", id:resp._id, Status:"OK"});
		},
		function (error){
			console.log("Error : Unable to create new plate");
			resReq.json({message:"Unable to create new Plate", error:error, Status:"KO"});
		}
	)
}

function getPlate(id, fileName, res){
	var plate = fs.readFileSync("./plate/" + id + "/" + fileName);
	res.writeHead(200, {'Content-Type': 'image/jpg'});
	res.end(plate, 'binary');
}

function getExtension(path) {
	var split = path.split('.');
	return (split[split.length-1]);
}

function savePlateFile(fileName, id, path){
	fs.readFile(path, function (err, data){
		var dirname = ".";
		var newPath = dirname + "/plate/" + id;
		fs.mkdir(newPath,function(err) {
			if (err) {
				console.log(err);
				return (false);
			}
			newPath = newPath + "/" + fileName + "." + getExtension(path);
			fs.writeFile(newPath, data, function (err) {
				if(err){
					console.log(err);
					return (false);
				}
				else {
					console.log("hello");
					return (true);
				}
			});
		});
	});
}

exports.newPlate = newPlate;
exports.getPlate = getPlate;
