<template>
    <div class="dashboard-template">
        <div class="welcome-container">
            <h1>Welcome, {{ username }}</h1>
            <button type="submit" @click="logout" class="logout-btn">LogOut</button>
        </div>
    </div>
</template>

<script>
export default {
    computed: {
        username() {
            return this.$route.query.username || 'Guest';
        }
    },
    methods: {
        logout() {
            this.$router.push('/login');
        }
    }
};
</script>

<style scoped>
.dashboard-template {
    display: flex;
    justify-content: center;
    align-items: center;
    min-height: 100px;
    background-color: #f4f6f9;
    font-family: 'Arial', sans-serif;
}

.welcome-container {
    text-align: center;
    background-color: #fff;
    padding: 30px;
    border-radius: 10px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    width: 100%;
    max-width: 400px;
    transition: all 0.3s ease-in-out;
}

.welcome-container h1 {
    font-size: 24px;
    color: #333;
    margin-bottom: 20px;
}

.logout-btn {
    background-color: #007bff;
    color: #fff;
    border: none;
    padding: 12px 20px;
    border-radius: 5px;
    cursor: pointer;
    font-size: 16px;
    transition: background-color 0.3s ease;
}

.logout-btn:hover {
    background-color: #0056b3;
}

.logout-btn:focus {
    outline: none;
}
</style>
