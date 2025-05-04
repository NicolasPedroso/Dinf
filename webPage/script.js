function trocarIdioma() {
  alert("Função de idioma ainda será implementada.");
}

// Tema claro/escuro com persistência
function alternarTema() {
  const body = document.body;
  body.classList.toggle('light');
  localStorage.setItem('tema', body.classList.contains('light') ? 'light' : 'dark');
}

// Mantém o tema ao recarregar a página
window.addEventListener('DOMContentLoaded', () => {
  const temaSalvo = localStorage.getItem('tema');
  if (temaSalvo === 'light') {
    document.body.classList.add('light');
  }
});

document.addEventListener("DOMContentLoaded", () => {
  const toggle = document.getElementById("theme-toggle");
  toggle.addEventListener("click", () => {
    const html = document.documentElement;
    const current = html.getAttribute("data-theme");
    html.setAttribute("data-theme", current === "dark" ? "light" : "dark");
    toggle.textContent = current === "dark" ? "☀️" : "🌙";
  });
});