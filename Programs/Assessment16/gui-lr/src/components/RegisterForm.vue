<template>
    <div class="register-form">
        <h1>Register</h1>
        <form @submit.prevent="submitForm">
            <div>
                <label for="username">Username: </label>
                <input type="text" v-model="username" required />
            </div>
            <div>
                <label for="password">Password: </label>
                <input type="password" v-model="password" required />
            </div>
            <div>
                <label for="email">Email: </label>
                <input type="email" v-model="email" required />
            </div>
            <button type="submit">Register</button>
        </form>
        <p v-if="errormessage" style="color: red;">{{ errormessage }}</p>
        <p>Already have an account? <router-link to="/login">Login</router-link></p>
    </div>
</template>


<script>
export default{
    data(){
        return{
            username: '',
            email: '',
            password: '',
            errormessage: ''
        };
    },
    methods: {
        async submitForm(){
            try{
                const response = await fetch('http://localhost:8888/register',{
                    method: 'POST',
                    headers: {
                        'Content-Type' : 'application/x-www-form-urlencoded' 
                    },
                    body: `username=${this.username}&password=${this.password}&email=${this.email}`
                });

                if(response.ok){
                    this.$router.push('/login');
                } else {
                    const text = await response.text();
                    this.errormessage = text;
                }
            }
            catch(error){
                    this.errormessage = 'Failed to connect to the server';
            }
        }
    }
};
</script>


<style scoped>
/* Register Form Container */
.register-form {
  max-width: 400px;            /* Maximum width for the form */
  margin: 0 auto;              /* Center the form horizontally */
  padding: 20px;               /* Add padding inside the form */
  border: 1px solid #ccc;     /* Light border around the form */
  border-radius: 8px;         /* Rounded corners */
  background-color: #fff;     /* White background for the form */
}

/* Style for Each Input Field Container */
.register-form div {
  margin-bottom: 15px;        /* Space between each form input field */
  display: flex;              /* Align label and input in a row */
  align-items: center;        /* Vertically align the label and input box */
  justify-content: space-between; /* Ensure label and input are spread out */
}

/* Label Style */
.register-form label {
  font-weight: bold;          /* Bold text for the label */
  margin-right: 10px;         /* Space between label and input */
  color: #e7bdbd;                /* Dark color for the label */
  width: 100px;               /* Fixed width for labels to align properly */
}

/* Input Field Style */
.register-form input {
  padding: 10px;              /* Add padding inside the input */
  border: 1px solid #ccc;     /* Light border around the input */
  border-radius: 5px;         /* Rounded corners for the input */
  width: calc(100% - 120px);   /* Make input take up the remaining space */
  box-sizing: border-box;     /* Include padding and border in the width calculation */
}

/* Button Style */
.register-form button {
  padding: 10px 20px;         /* Padding for the button */
  background-color: #ff6a00;  /* Orange background for the button */
  border: none;               /* Remove border */
  border-radius: 5px;         /* Rounded corners */
  color: white;               /* White text color */
  cursor: pointer;            /* Change cursor to pointer */
  width: 100%;                /* Make button take up the full width */
  transition: background-color 0.3s ease; /* Smooth transition for the hover effect */
}

/* Button Hover Style */
.register-form button:hover {
  background-color: #ee0979;  /* Darker color when hovering over the button */
}

</style>