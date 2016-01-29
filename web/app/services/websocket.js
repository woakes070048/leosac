import Ember from 'ember';

export default Ember.Service.extend({
  ws: null,
  callback: [],
  beforeOpen: [],

  init()
  {
    "use strict";
    console.log('Service is initializing ...');

    var ws = this.get('ws');
    ws = new WebSocket('ws://localhost:8888/websocket');

    var self = this;

    ws.onopen = function ()
    {
      console.log('WS opened');

      // Process item that were queued before the connection
      // was ready.
      var queue = self.get('beforeOpen');
      if (queue.length > 0)
      {
        queue.forEach(function (payload)
        {
          ws.send(JSON.stringify(payload));
        });
        queue = [];
      }
      self.set('beforeOpen', queue);
    };

    ws.onmessage = function (event)
    {
      console.log(event.data);
      var obj = JSON.parse(event.data);
      console.log(obj);
      var cb = self.get('callback')[obj.uuid];
      cb.success(obj.content);
      delete self.get('callback')[obj.uuid];
    };

    ws.onclose = function (event)
    {
      console.log('WS was closed');
    };
    this.set('ws', ws);
  },

  sendJson(req_id, obj)
  {
    "use strict";

    var queue = this.get('beforeOpen');
    var ws = this.get('ws');
    var callback = this.get('callback');
    var request = {
      uuid: req_id,
      content: obj
    };

    if (ws.readyState === 1)
    {
      ws.send(JSON.stringify(request));
    }
    else
    {
      queue.push(request);
    }

    return new Ember.RSVP.Promise(function (resolve, reject)
    {
      var on_success = function (data)
      {
        console.log("HEREHEHREHRHERHEHREH");
        var d = [{id: 0, username: 'lama'},
          {id: 1, username:'titi', firstname: 'Blaa'}];
        Ember.run(null, resolve, d);
      };
      var on_error = function (why)
      {
        Ember.run(null, reject, why);
      };
      var cb = {
        success: on_success,
        error: on_error
      };
      callback[request.uuid] = cb;
    });
  },

  wsQuery()
  {
    "use strict";
    console.log("INSIDE WEBSOCKET SERVICE !!");
    //this.get('ws').send('LAMASTICOT');
  }

});
