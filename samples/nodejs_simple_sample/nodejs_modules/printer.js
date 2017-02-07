'use strict';

module.exports = {
    broker: null,
    configuration: null,
    intervalID: -1,

    create: function (broker, configuration) {
        this.broker = broker;
        this.configuration = configuration;

        return true;
    },

    start: () => {
        // this.intervalID = setInterval(() =>
        //     console.log(`start.lambda - ${Date.now()}`), 500
        // );
    },

    receive: function (message) {
        let data = Buffer.from(message.content).toString('utf8');
        console.log(`printer.receive - ${data}`);
    },

    destroy: function () {
        console.log('printer.destroy');
        if(this.intervalID !== -1) {
            clearInterval(this.intervalID);
        }
    }
};
