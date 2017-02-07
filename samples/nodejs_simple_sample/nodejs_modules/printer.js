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
        console.log(`printer.receive - ${message.content.join(', ')}`);
    },

    destroy: function () {
        console.log('printer.destroy');
        if(this.intervalID !== -1) {
            clearInterval(this.intervalID);
        }
    }
};
