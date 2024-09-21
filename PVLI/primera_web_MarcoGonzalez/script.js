function desaparece(nombre) {
	let items = document.getElementsByClassName(nombre);
  console.log(items);
  for(let i = 0; i < items.length; i++)
  {
    console.log(items[i].style.visibility)
    if(items[i].style.visibility == 'hidden')
    {
      items[i].style.visibility = 'visible';
    }
    else
    {
      items[i].style.visibility = 'hidden';
    }
  }
}

function coloresCambian(nom1, nom2)
{
  let items1 = document.getElementsByClassName(nom1);
  for(let i = 0; i < items1.length; i++)
  {
    items1[i].style.color = 'magenta';
  }
  let items2 = document.getElementsByClassName(nom2);
  for(let i = 0; i < items2.length; i++)
  {
    items2[i].style.color = 'darkgreen';
  }
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