// Crea eventos para la lectura de los sensores
if (!!window.EventSource) {
    var source = new EventSource('/events');
  
    source.addEventListener('open', function(e) {
      console.log("Events Connected");
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/nuevo", true);
      console.log("Solicitud de valores iniciales");
      xhr.send();
    }, false);
  
    source.addEventListener('error', function(e) {
      if (e.target.readyState != EventSource.OPEN) {
        console.log("Events Disconnected");
      }
    }, false);
  
    source.addEventListener('perro_salchicha', function(e) {
      console.log("perro_salchicha", e.data);
      var obj = JSON.parse(e.data);
      document.getElementById("iPot").innerHTML = obj.Pot;
      document.getElementById("iLDR").innerHTML = obj.LDR;
      document.getElementById("iCT").innerHTML = obj.CT;
      document.getElementById("led_sta").innerHTML = obj.led_sta;
      document.getElementById("pwmSlider").value = obj.CT;
    }, false);
  
    source.addEventListener('move', function(e) {
      console.log("Mover Servo", e.data);
      var obj = JSON.parse(e.data);
      document.getElementById("iPot").innerHTML = obj.Pot;
      document.getElementById("iLDR").innerHTML = obj.LDR;
      document.getElementById("iCT").innerHTML = obj.CT;
      document.getElementById("led_sta").innerHTML = obj.led_sta;
      document.getElementById("pwmSlider").value = obj.CT;
    }, false);
  
  
  }
  
  // Envío por presión del botón
  function toggleBoton(element){
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/"+element.id, true);
    console.log(element.id);
    xhr.send();
  }
  
  // Envío por cambio en el Slider
  function updateSliderPWM(element) {
    var sliderValue = document.getElementById("pwmSlider").value;
    document.getElementById("iCT").innerHTML = sliderValue;
    console.log(sliderValue);
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/slider?value="+sliderValue, true);
    xhr.send();
  }
  
  // Función para abrir las pestañas
  function openTab(evt, tabName) {
    document.querySelectorAll('.tab-content').forEach(tab => tab.style.display = 'none');
    document.querySelectorAll('.tab').forEach(tab => tab.classList.remove('active'));
    document.getElementById(tabName).style.display = 'block';
    evt.currentTarget.classList.add('active');
  
  
 // Cambiar solo la imagen dinámica (no la fija)
 const imagenDinamica = document.getElementById('imagen-dinamica');
 if (imagenDinamica){
 switch(tabName) {
   case 'pestana1':
     imagenDinamica.src = 'servo1.jpeg';
     break;
   case 'pestana2':
     imagenDinamica.src = 'servo2.jpeg';
     break;
   case 'pestana3':
     imagenDinamica.src = 'servo3.jpeg';
     break;
   case 'pestana4':
     imagenDinamica.src = 'servo4.jpeg';
     break; 
   case 'pestana5':
    imagenDinamica.src = 'confi.jpeg';
     break;
    default:
     imagenDinamica.src = 'servo1.jpeg';
 }
}
  }



  // Funciones para manejar los formularios
  function submitForm(servo) {
    const activeTab = document.querySelector('.tab-content:not([style*="display: none"])');
    const valueInput = activeTab.querySelector("input[name='value']");
    const type = activeTab.querySelector("input[name='type']:checked").value;
    const value = valueInput.value.trim();
  
    if (value === "" || isNaN(value)) {
      alert("⚠️ Por favor, ingresa un número válido en el campo de valor.");
      valueInput.focus();
      return;
    }
  
    alert('✅ Movimiento enviado al Servo ' + servo + ' con ' + value + ' ' + type);
  }
  
  function submitTrayectoria(servo) {
    alert('Parámetros cambiados para el Servo ' + servo);
  }
  
  function addPoint(servo) {
    const activeTab = document.querySelector('.tab-content:not([style*="display: none"])');
    const valueInput = activeTab.querySelector("input[name='position']");
    const type = activeTab.querySelector("input[name='type']:checked").value;
    const value = valueInput.value.trim();
  
    if (value === "" || isNaN(value)) {
      alert("⚠️ Por favor, ingresa un número válido en el campo de valor.");
      valueInput.focus();
      return;
    }
      alert(' ✅ Punto agregado para el Servo ' + servo + ' con ' + value + ' ' + type);
       
  }
  
  function addPoint(servo) {
    alert('Punto agregado para el Servo ' + servo);
  }
  
  function executeSequence() {
    alert('Ejecutando secuencia alternada...');
  }
  
  // Actualizar estado cada segundo
  setInterval(() => {
    // Simulación de estado
    const status = "Listo";
    const step = 0;
    document.getElementById('estado-ejecucion').textContent = status;
    document.getElementById('paso-actual').textContent = step;
  }, 1000);