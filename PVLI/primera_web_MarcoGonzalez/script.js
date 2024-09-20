function devuelveTextoDeAlerta() {
  return "uooooo! Vaya alerta";
}

function desaparece(nombre) {
	let button = document.getElementById(nombre);
  button.style.visibility='hidden';
}

function playMusic(musica){
  const audio = document.getElementById(musica);
  audio.volume = 0.25; 
  audio.play();
}

function playButton(musica, button, displayContent)
{
  playMusic(musica);

  let loader = document.getElementById(button);
  loader.style.display = "none";

  let content = document.getElementById(displayContent);
  content.style.display = "block";

  document.body.style.backgroundImage = "url('resources/background.gif')";
  document.body.style.backgroundAttachment = "fixed";
  document.body.style.backgroundRepeat = "no-repeat";
  document.body.style.backgroundSize = "cover";
  document.body.style.height = "100%";


}