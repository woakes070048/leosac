import Ember from 'ember';

export default Ember.Component.extend({
  websocket: Ember.inject.service('websocket'),
  globalInfo: Ember.inject.service('leosac-info'),
  isLoginFailed: false,
  username: '',
  password: '',
  actions: {
    login()
    {
      console.log("Login in progress... " + this.get('username'));

      var self=this;
      var ws = this.get('websocket');
      ws.sendJson('create_auth_token',
        {
          username: this.get('username'),
          password: this.get('password')
        }).then(function (data)
      {
        "use strict";
        if (data.status === 0) // success
        {
          var gi = self.get('globalInfo');
          gi.setCurrentUser(self.get('username'));

          // Store auth token in local storage

        }
        else
        {
          self.set('isLoginFailed', true);
        }
      });


    }
  }
});
