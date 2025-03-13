<template>
  <div id="app">
    <router-view></router-view>
  </div>
</template>

<script>
export default {
  name: 'App',
};
</script>

<style scoped>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

html, body {
  height: 100%;
  font-family: 'Arial', sans-serif;
}

/* Full-screen background gradient */
#app {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;  /* Ensures the background covers the full screen height */
  background: linear-gradient(135deg, #ff6a00, #ee0979);  /* Gradient background from orange to pink */
  color: white;
  text-align: center;
}

/* Add a bit of padding and border radius to the container */
#app > * {
  padding: 20px;
  border-radius: 10px;
  background-color: rgba(0, 0, 0, 0.5);  /* Slight dark background behind the content */
}

/* Add some margin to the bottom */
body {
  margin: 0;
}
</style>
