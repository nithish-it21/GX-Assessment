import Vue from 'vue';  // Import Vue
import App from './App.vue';  // Import your main App component
import router from './router.js';  // Import the router configuration

Vue.config.productionTip = false;  // Disable production tip

// Create a new Vue instance and mount it to the DOM
new Vue({
  render: h => h(App),
  router,  // Pass the router to the Vue instance
}).$mount('#app');
