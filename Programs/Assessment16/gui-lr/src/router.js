import Vue from 'vue';
import VueRouter from 'vue-router';
import DashboardForm from './components/DashboardForm.vue';  // Corrected import path
import LoginForm from './components/LoginForm.vue';
import RegisterForm from './components/RegisterForm.vue';

Vue.use(VueRouter);

const routes = [
  {
    path: '/',
    redirect: '/login',
  },
  {
    path: '/login',
    name: 'Login',
    component: LoginForm,
  },
  {
    path: '/dashboard',
    name: 'dashboard',
    component: DashboardForm,  // Correct component name here as well
  },
  {
    path: '/register',
    name: 'Register',
    component: RegisterForm,
  },
];

const router = new VueRouter({
  routes,
  mode: 'history',
});

export default router;
