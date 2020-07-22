GeoBOS.hello = {
		getVersion: function (cb){
			GeoBOS.plugin.execute('HelloPlugin','getVersion', GeoBOS.getId(), '1 2', null, cb);			
			},
			getBuildTime: function (cb){
			GeoBOS.plugin.execute('HelloPlugin','getBuildTime', GeoBOS.getId(), '', null, cb);	
			}		
				
}