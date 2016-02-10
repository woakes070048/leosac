import Ember from 'ember';

export default Ember.Route.extend({
  globalInfo: Ember.inject.service('leosac-info'),

  model() {
    "use strict";
    return this.store.findAll('user');
  }
});
