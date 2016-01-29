import DS from 'ember-data';

export default DS.Adapter.extend({
  ws: Ember.inject.service('websocket'),

  findAll: function (store, type, sinceToken)
  {
    console.log('Type is: ' + type);
    console.log("HELLO ADAPTING");

    this.get('ws').wsQuery();

    console.log(sinceToken);

    //store.push('user', {id:42, username: 'toto'});

    var ws = this.get('ws');
    var p = ws.sendJson(1, {'cmd': 'getUsers'});
    {

    };
    var p2 = p.then(function (data)
    {
      "use strict";

      console.log(data);

      store.push('user', {id: 0, username: 'lama'});
    });

    console.log(p);
    console.log("P2 VALUE");
    console.log(p2);

    return p2;
  }
});
