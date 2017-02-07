'use strict';

module.exports = {
    broker: null,
    configuration: null,
    intervalID: -1,

    create: function (broker, configuration) {
        this.broker = broker;
        this.configuration = Object.assign({}, {
            deviceName: '',
            deviceKey: ''
        }, configuration);

        return true;
    },

    start: function () {
        this.intervalID = setInterval(() => {
            let data = [
                Math.random() * 50,
                Math.random() * 50
            ];
            let buffer = Buffer.from(JSON.stringify(data), 'utf8');
            let content = new Uint8Array(buffer);

            this.broker.publish({
                properties: {
                    'source': 'mapping',
                    'deviceName': this.configuration.deviceName,
                    'deviceKey': this.configuration.deviceKey
                },
                content: content
            });
        }, 500);
    },

    receive: function(message) {
    },

    destroy: function() {
        console.log('sensor.destroy');
        if(this.intervalID !== -1) {
            clearInterval(this.intervalID);
        }
    }
};
