import axios from "axios";

const parseBackend = axios.create({
    baseURL: "http://localhost:8080/"
});
export default parseBackend;