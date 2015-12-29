plateRecognition.factory('plate', ['$http','elasticClient','main',function($http, elasticClient, main){
  var plateObj = {};
  var client = elasticClient.getClient(conf.elasticsearchServer);

  plateObj.info = {};
  plateObj.info.from = 0;
  plateObj.info.size = 10;
  plateObj.info.page = 1;
  plateObj.info.maxPage = 0;

  plateObj.info.requestText = "";

  plateObj.search = function(from, to, req) {
    request = ejs.Request();
    query = ejs.QueryStringQuery();
    if (req === "") {
      query = ejs.MatchAllQuery();
    }
    else {
      query.query(req);
    }
    request.query(query);
    request.size(to - from);
    request.from(from);
    client.search({index:conf.elasticsearchIndex, body:request})
    .then(function(resp){
      plateObj.info.resp = resp;
      plateObj.info.plateList = resp.hits.hits;
      // Update Pager
      plateObj.info.maxPage = Math.round(resp.hits.total / plateObj.info.size);
      console.log(plateObj.info.maxPage);
    },
    function (error){
      plateObj.info.resp = error;
    });
  };

  plateObj.prev = function () {
  if (plateObj.info.page > 1) {
      plateObj.info.page--;
      plateObj.info.from -= plateObj.info.size;
      if (plateObj.info.from < 0){
        plateObj.info.from = 0;
      }
      plateObj.search(plateObj.info.from,plateObj.info.from + plateObj.info.size, plateObj.info.requestText);
    }
  };

  plateObj.next = function () {
    if (plateObj.info.page < plateObj.info.maxPage){
        plateObj.info.page++;
        plateObj.info.from += plateObj.info.size;
        plateObj.search(plateObj.info.from,plateObj.info.from + plateObj.info.size, plateObj.info.requestText);
    }
  };
  
  plateObj.getPlateList = function (){
    plateObj.info.page = 1;
    plateObj.info.from = 0;
    plateObj.search(plateObj.info.from,plateObj.info.from + plateObj.info.size, plateObj.info.requestText);
  };

  plateObj.removePlate = function (){
     // TODO : Remove plate
  };

  plateObj.editPlate = function (index) {
      plateObj.info.selectedPlateIdx = index;
      plateObj.info.selectedPlate = plateObj.info.plateList[index];
      main.info.tab = 4;
  };

  return (plateObj);
}]);
