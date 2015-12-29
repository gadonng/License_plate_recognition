var plate = require('../modules/plates.js');

module.exports = function(app) {
    app.all('/*', function (req, res, next){
        res.header("Access-Control-Allow-Origin", "*");
        res.header("Access-Control-Allow-Methods", 'GET,PUT,POST,DELETE');
        res.header("Access-Control-Allow-Origin", "X-Requested-Width", "Content-Type");
        next();
    });
    app.get('/',function(req,res){
        res.end("Node-File-Upload");
        console.log("adazd");
    });
    app.post('/plate/', function(req, res) {
        plate.newPlate(req.files.file.path, res);
    });

    app.get('/plate/:id/:filename', function(req, res){
        plate.getPlate(req.params.id, req.params.filename, res);
    });
};
