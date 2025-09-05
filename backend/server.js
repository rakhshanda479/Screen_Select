function renderMovies(list) {
  results.innerHTML = '';
  if (!list.length) {
    results.innerHTML = '<div class="text-sm opacity-70">No results.</div>';
    return;
  }
  list.forEach(m => {
    const card = document.createElement('div');
    card.className = 'card overflow-hidden';

    // Poster image (placeholder based on title seed)
    const posterUrl = `https://picsum.photos/seed/${encodeURIComponent(m.title)}/300/180`;

    card.innerHTML = `
      <img src="${posterUrl}" alt="${m.title}" class="w-full h-40 object-cover rounded-t-2xl">
      <div class="p-3 space-y-2">
        <div class="flex items-start justify-between">
          <div class="font-semibold text-indigo-700">${m.title}</div>
          <div class="badge">⭐ ${m.rating}</div>
        </div>
        <div class="text-sm opacity-70">${m.director}</div>
        <div class="flex flex-wrap gap-2 text-xs">
          <span class="badge">${m.genre}</span>
          <span class="badge">${m.type}</span>
          <span class="badge">${m.releasedYear}</span>
        </div>
        <button class="mt-2 px-3 py-1 rounded-xl bg-indigo-500 text-white text-sm hover:bg-indigo-600 w-full">
          ➕ Add to History
        </button>
      </div>
    `;

    // Add-to-history button
    const btn = card.querySelector('button');
    btn.addEventListener('click', (e) => {
      e.stopPropagation();
      const arr = getHistory();
      if (!arr.includes(m.title)) {
        arr.push(m.title);
        setHistory(arr);
        renderHistory();
        toast('Added to history');
      }
    });

    // (Optional) whole card clickable
    card.addEventListener('click', () => {
      const arr = getHistory();
      if (!arr.includes(m.title)) {
        arr.push(m.title);
        setHistory(arr);
        renderHistory();
        toast('Added to history');
      }
    });

    results.appendChild(card);
  });
}
