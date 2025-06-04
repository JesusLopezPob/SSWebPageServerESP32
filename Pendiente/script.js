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
  
  
    for (let i = 1; i <= 4; i++) {
      source.addEventListener(`servo${i}`, function(e) {
        console.log(`Movimiento en Servo ${i}:`, obj);
        var obj = JSON.parse(e.data);
        document.getElementById(`status_servo${i}`).innerText = `Posición: ${obj.value}`;
      }, false);
    }

    for (let i = 1; i <= 4; i++) {
      source.addEventListener(`pointAdd${i}`, function(e) {
        console.log(`Punto agregado a servo  ${i}:`, obj);
        var obj = JSON.parse(e.data);
        document.getElementById(`status_servo${i}`).innerText = `Posición: ${obj.value}`;
      }, false);
    }
  
    for (let i = 1; i <= 3; i++) {
      source.addEventListener(`MoveParam${i}`, function(e) {
        console.log(`Parametros cambiados  al servo  ${i}:`, obj);
        var obj = JSON.parse(e.data);
        document.getElementById(`status_servo${i}`).innerText = `Posición: ${obj.value}`;
      }, false);
    }   
    
    source.addEventListener(`startSeq`, function(e) {
      console.log(`Se inicia la secuencia:`, obj);
      var obj = JSON.parse(e.data);
      document.getElementById(`status_servo${i}`).innerText = `Posición: ${obj.value}`;
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



  // Funciones para manejar los botones de confirmacion


  function submitForm(servo) {
    const activeTab = document.querySelector('.tab-content:not([style*="display: none"])');
    const valueInput = activeTab.querySelector("input[name='value']");
    const typeInput = activeTab.querySelector("input[name='type']:checked");
  
    const value = valueInput.value.trim();
    const type = typeInput.value;
  
    if (value === "" || isNaN(value)) {
      alert("⚠️ Ingresa un número válido.");
      valueInput.focus();
      return;
    }
  
    // Enviar al ESP32 vía GET sin recargar
    const xhr = new XMLHttpRequest();
    xhr.open("GET", `/move?servo=${servo}&type=${type}&value=${value}`, true);
    xhr.send();
    
    //tabla ex
    document.getElementById(`tabla-pos${servo}`).textContent = value;
  document.getElementById(`tabla-tipo${servo}`).textContent = type;






    alert('✅ Movimiento enviado al Servo ' + servo + ' con ' + value + ' ' + type);
    console.log(`✅ Movimiento enviado al Servo ${servo}: ${value} (${type})`);
    
    // Si quieres mostrar feedback visual:
    //document.getElementById(`status_servo${servo}`).innerText = `Enviado: ${value} ${type}`;

  }
  


    

  function addPoint(servo) {
    // Detecta la pestaña visible
    const activeTab = document.querySelector('.tab-content:not([style*="display: none"])');
    const valueInput = activeTab.querySelector("input[name='position']");
    const typeInput = activeTab.querySelector("input[name='Type']:checked");
  
    const pos = valueInput.value.trim();
    const Type = typeInput.value;
  
    if (pos === "" || isNaN(pos)) {
      alert("⚠️ Por favor, ingresa un número válido.");
      valueInput.focus();
      return;
    }
  
    // Enviar punto al servidor
    const xhr = new XMLHttpRequest();
    xhr.open("GET", `/addPoint?servo=${servo}&type=${Type}&value=${pos}`, true);
    xhr.send();
  
    alert(' ✅ Punto agregado para el Servo ' + servo + ' con ' + pos + ' ' + Type);

    console.log(`🟢 Punto agregado → Servo ${servo} | ${pos} ${Type}`);
    
    //document.getElementById(`status_servo${servo}`).innerText = `Punto: ${value} ${type}`;
  }
  
 function submitMoveParame(servo){
     // Detecta la pestaña visible
     const activeTab = document.querySelector('.tab-content:not([style*="display: none"])');
     const valueInputP = activeTab.querySelector("input[name='p']"); 
     const valueInputI = activeTab.querySelector("input[name='i']"); 
     const valueInputD = activeTab.querySelector("input[name='d']"); 

     const valueInputV = activeTab.querySelector("input[name='v']"); 
     const valueInputA = activeTab.querySelector("input[name='a']");      


     const valueP = valueInputP.value.trim(); 
     const valueI = valueInputI.value.trim(); 
     const valueD = valueInputD.value.trim(); 

     const valueV = valueInputV.value.trim(); 
     const valueA = valueInputA.value.trim(); 

         // Enviar al ESP32 vía GET sin recargar
    const xhr = new XMLHttpRequest();
    xhr.open("GET", `/moveParamet?servo=${servo}&p=${valueP}&i=${valueI}&d=${valueD}&v=${valueV}&a=${valueA}`, true);
    xhr.send();

    //tabla ex
 document.getElementById(`tabla-pid${servo}`).textContent = `${valueP} / ${valueI} / ${valueD}`;
  document.getElementById(`tabla-vel${servo}`).textContent = valueV;
  document.getElementById(`tabla-ace${servo}`).textContent = valueA;


    alert(' ✅ Parametros cambiados al servo ' + servo + ' con  P:' + valueP + ' I:' + valueI + ' D:' + valueD + ' V:' + valueV + ' A:' + valueA);

 }
  
  function executeSequence() {
     // Enviar al ESP32 vía GET sin recargar
    const xhr = new XMLHttpRequest();
    xhr.open("GET", `/Start?`, true);
    xhr.send();
  
    alert('✅ Ejecutando secuencia alternada...');
    console.log(`✅ Ejecutando secuencia alternada...)`);
    
  }
  

  
  // Actualizar estado cada segundo
  setInterval(() => {
    // Simulación de estado
    const status = "Listo";
    const step = 0;
    document.getElementById('estado-ejecucion').textContent = status;
    document.getElementById('paso-actual').textContent = step;
  }, 1000);
 
// tabla 
  function escanearValores() {
  for (let servo = 1; servo <= 4; servo++) {
    const tabContent = document.getElementById(`pestana${servo}`);

    const inputId = tabContent.querySelector(`#id-servo${servo}`)?.value || "--";
    const baudSelect = tabContent.querySelector(`#baud-servo${servo}`);
    const baudRate = baudSelect ? baudSelect.options[baudSelect.selectedIndex].value : "--";

    document.getElementById(`tabla-id${servo}`).textContent = inputId;
    document.getElementById(`tabla-baud${servo}`).textContent = baudRate;

    const inputP = tabContent.querySelector("input[name='p']")?.value || "--";
    const inputI = tabContent.querySelector("input[name='i']")?.value || "--";
    const inputD = tabContent.querySelector("input[name='d']")?.value || "--";
    document.getElementById(`tabla-pid${servo}`).textContent = `${inputP} / ${inputI} / ${inputD}`;

    const inputV = tabContent.querySelector("input[name='v']")?.value || "--";
    const inputA = tabContent.querySelector("input[name='a']")?.value || "--";
    document.getElementById(`tabla-vel${servo}`).textContent = inputV;
    document.getElementById(`tabla-ace${servo}`).textContent = inputA;
  }

  alert(" Datos actualizados correctamente en la tabla.");
}
