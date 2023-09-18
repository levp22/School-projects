import './App.css';
import Countup  from './features/countup/Countup'
import {Sound} from './features/sound/Sound';
import { Footer } from './features/footer/Footer';

function App() {
  return (
    <div>
      <Countup />
      <Sound />
      <Footer/>
    </div>
  );
}

export default App;