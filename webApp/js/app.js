/**
*  Module plateRecogntion
*
* Description
* Search engine for license plate 
*/

var plateRecognition = angular.module('plateRecognition', ['elasticjs.service', 'elasticsearch', 'lr.upload']);
plateRecognition.service('elasticClient', function(esFactory) {
		return { 
			getClient: function(server) {
				return esFactory({host: server,});
			}
		}
	}
);

plateRecognition.config(['$httpProvider',function($httpProvider) {
	$httpProvider.defaults.headers.useXDomain = true;
	delete $httpProvider.defaults.headers.common['X-Requested-With'];
}]);