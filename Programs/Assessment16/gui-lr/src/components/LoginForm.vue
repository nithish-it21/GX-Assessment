<template>
    <div class="login-form">
        <h1>Login</h1>
        <form @submit.prevent="submitForm">
            <div>
                <label for="username">Username: </label>
                <input type="text" v-model="username" required />
            </div>
            <div>
                <label for="password">Password: </label>
                <input type="password" v-model="password" required />
            </div>
            <button type="submit">Login</button>
        </form>
        <p v-if="errorMessage" style="color: red;">{{ errorMessage }}</p>
        <p>Don't have an account? <router-link to="/register">Register</router-link></p>
    </div>
</template>

<script>
export default {
    data() {
        return {
            username: '',
            password: '',
            errorMessage: ''
        };
    },
    methods: {
        async submitForm() {
            try {
                const formData = new URLSearchParams();
                formData.append('username', this.username);
                formData.append('password', this.password);

                const response = await fetch('http://localhost:8888/login', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded'
                    },
                    body: formData
                });

                if (response.ok) {
                    // Redirect to the dashboard with username as query parameter
                    this.$router.push({ name: 'dashboard', query: { username: this.username } });
                } else {
                    const text = await response.text();
                    this.errorMessage = text || 'Incorrect Username or Password';
                }
            } catch (error) {
                this.errorMessage = 'Failed to connect to the server';
            }
        }
    }
}
</script>

<style scoped>
.login-form {
  max-width: 400px;
  margin: 0 auto;
  padding: 20px;
  border: 1px solid #ccc;
  border-radius: 8px;
  background-color: #fff;
}
.login-form div {
  margin-bottom: 15px;
  display: flex;
  align-items: center;
  justify-content: space-between;
}
.login-form label {
  font-weight: bold;
  margin-right: 10px;
  color: #e7bdbd;
  width: 100px;
}
.login-form input {
  padding: 10px;
  border: 1px solid #ccc;
  border-radius: 5px;
  width: calc(100% - 120px);
}
.login-form button {
  padding: 10px 20px;
  background-color: #ff6a00;
  border: none;
  border-radius: 5px;
  color: white;
  cursor: pointer;
  width: 100%;
}
.login-form button:hover {
  background-color: #ee0979;
}
</style>
